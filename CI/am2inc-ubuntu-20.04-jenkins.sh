#!/bin/bash
#
# A CI job uses two shell scripts: This one, which runs in the host context as
# the CI user, and a second one inside the container, named
# CI/allmodels-ubuntu-20.04-make-dpkg.sh.
#

# Fail hard
set -xe

IMAGE=cross/ubuntu-20.04-lts-x64/am2inc
docker build -t ${IMAGE} -f CI/am2inc-ubuntu-20.04.dockerfile CI

# Create an entrypoint for the docker container, which maps the ids of
# user and group 'devel' to the ids of current user and group ('jenkins').
#
# This allows us to execute commands with sudo as required by checkinstall.
# Otherwise checkinstall will pack the installer artifacts with an invalid
# non-root user id as owner.
#
# The entrypoint has to be executed as user root by adding parameter '-u0' to
# 'docker run' command.
ENTRYPOINT_FILE=${WORKSPACE_TMP-/tmp}/.jenkins_entrypoint
cat > ${ENTRYPOINT_FILE} <<- EOM
#!/bin/bash
set -ex
usermod -u $(id -u) devel
groupmod -g $(id -g) devel
sudo -u devel -E --preserve-env=PATH \$@
EOM
chmod +x ${ENTRYPOINT_FILE}

sudo docker run --rm \
    \
    -u0 \
    -v $ENTRYPOINT_FILE:/.entrypoint:ro \
    --entrypoint="/.entrypoint" \
    \
    -v /home/matthias/Development/ModelImporter/AmaltheaImporter:/home/matthias/Development/ModelImporter/AmaltheaImporter \
    -v $PWD:$PWD -w $PWD \
    -v $HOME/.ccache:/home/devel/.ccache \
    -v $HOME/.subversion:/home/devel/.subversion \
    -v $PWD/.local:/home/devel/.local \
    -v $PWD/.qt:/home/devel/.qt \
    --cap-add=SYS_PTRACE --privileged \
    -e INCHRONLIBS=/opt/inchron \
    \
    -e DEBIAN=ubuntu \
    \
    -e BUILD_NUMBER="$BUILD_NUMBER" -e JOB_NAME="$JOB_NAME" \
    ${IMAGE} \
    ./CI/am2inc-ubuntu-make-dpkg.sh
