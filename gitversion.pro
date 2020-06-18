#
# gitversion.pro
#
TEMPLATE = aux

gitversion.h.commands = @echo updating gitversion.h if necessary && ./gitversion.sh
gitversion.h.depends = gitversion.sh FORCE

all.depends += gitversion.h
install.depends += all

QMAKE_EXTRA_TARGETS += gitversion.h all install