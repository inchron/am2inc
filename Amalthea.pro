#
# Amalthea/Amalthea.pro
#

TEMPLATE = subdirs

SUBDIRS += Amalthea Mapping Application

Application.depends += Amalthea Mapping
Mapping.depends += Amalthea
