#!/bin/sh

# Fail hard
set -xe

#
# /etc/os-release is parsed as https://unix.stackexchange.com/a/498788
#
# See also https://unix.stackexchange.com/a/433245 for a quite interesting
# discussion of the topic.
ID=$(grep -oP '(?<=^ID=).+' /etc/os-release | tr -d '"')
if [ "$ID" != "ubuntu" ] ; then
    echo "This OS $ID is not supported as build host."
    exit 1
fi

# The list of required packages (at runtime) contains some version-dependent
# names [SUITE3-3774].
VERSION=$(grep -oP '(?<=^VERSION_ID=).+' /etc/os-release | tr -d '"')
case "$VERSION" in
    20.04)
        ;;
    22.04)
        ;;
    *)
        echo "This configuration $OS:$VERSION is not supported as build host."
        exit 1
        ;;
esac


#
# checkinstall tracks all filesystem operations of "make install". Files,
# which are created, are packed into the installer. Hence it is important,
# that "make all" does not install anything or that "make install" copies
# everything unconditionally
#
# Note: Do not use parallelism for checkinstall, it will come to race
# conditions between concurrent instances of linuxdeployqt.
#

echo "CONFIG -= debug" > local.pri
echo "CONFIG += release" >> local.pri
echo "CONFIG += ndebug" >> local.pri
echo "QMAKE_CXXFLAGS += -DNDEBUG -D_NDEBUG" >> local.pri

# Reset build info independently of git-checkout options
rm -f gitversion.h Application/release/.obj/Options.o

# force something like a "make clean"
touch $(find . -name "*.pro")
/opt/inchron/qt5/bin/qmake

make -j 22

BUILD_NUMBER=${BUILD_NUMBER:-0}

RELEASE=$(cat RELEASE).${BUILD_NUMBER}
DATE=$(date +%Y%m%d)
TAG=$(git describe --always)

echo "INCHRON Amalthea Model Importer" > description-pak
[ -d "doc-pak" ] || mkdir doc-pak

# Execute checkinstall with sudo, otherwise artifacts in the installer will
# have non-root ownership.
sudo -E --preserve-env=PATH checkinstall \
    --requires "libglib2.0-0" \
    --reset-uids \
    --install=no \
    --backup=no \
    --pkgname="inchron-am2inc" \
    --pkglicense="INCHRON Software License Agreement" \
    --maintainer="support@inchron.com" \
    --pkgversion=${RELEASE} \
    --pkgrelease=${DATE} \
    --exclude="/home,/opt/am2inc/AppRun,/opt/am2inc/bin/qt.conf,/opt/AppRun,/proc,/usr" \
    --nodoc \
    -y \

sudo chown -R "$(whoami)": .

rm description-pak
