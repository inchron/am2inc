#
# Amalthea/Amalthea.pro
#

TEMPLATE = subdirs

SUBDIRS += \
    Amalthea \
    Application \
    Mapping \
    Root \
    gitversion \

gitversion.file = gitversion.pro

Amalthea.depends += gitversion
Mapping.depends += gitversion Amalthea Root
Application.depends += Amalthea Mapping Root
