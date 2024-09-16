#
# Use the default image and prepare some specifics which can only be done as
#  root
#
FROM registry.inchron.de/cross/ubuntu-20.04-lts-x64/chronsuite3

# [AM2INC-29] Prepare an installation directory for am2inc
ARG PREFIX_AM2INC=/opt/am2inc

RUN mkdir -p ${PREFIX_AM2INC}/lib/checkinstall/ && \
    ln -s /usr/lib/checkinstall/installwatch.so ${PREFIX_AM2INC}/lib/checkinstall/installwatch.so && \
    chown -R devel ${PREFIX_AM2INC} && \
    chmod -R a+w   ${PREFIX_AM2INC}

ENV PREFIX=${PREFIX_AM2INC}
