#!/bin/sh

set -e

#
# The default build container is only prepared for the main tools. Others must
# be setup manually.
#
USER=$(id -u)
sudo mkdir $PREFIX && sudo chown $USER $PREFIX
mkdir -p $PREFIX/lib/checkinstall
ln -s /usr/lib/checkinstall/installwatch.so $PREFIX/lib/checkinstall/installwatch.so

#
# checkinstall tracks all filesystem operations of "make install". Files,
# which are created, are packed into the installer. Hence it is important,
# that "make all" does not install anything or that "make install" copies
# everything unconditionally
#
make -j 22

BUILD_NUMBER=${BUILD_NUMBER:-0}

RELEASE=$(cat RELEASE).${BUILD_NUMBER}
DATE=$(date +%Y%m%d)
TAG=$(git describe --always)

echo "INCHRON Amalthea Model Importer" > description-pak
[ -d "doc-pak" ] || mkdir doc-pak

checkinstall \
    --requires "libglib2.0-0" \
    --install=no \
    --backup=no \
    --pkgname="inchron-am2inc" \
    --pkglicense="INCHRON Software License Agreement" \
    --maintainer="support@inchron.com" \
    --pkgversion=${RELEASE} \
    --pkgrelease=${DATE} \
    --exclude="/home" \
    --nodoc \
    -y \

rm description-pak

#
# apt update && apt-get install -y ./ToolSuite/inchron-am2inc_ <TAB>
#
# /opt/am2inc/bin/am2inc in.amxmi out.iprx
#
