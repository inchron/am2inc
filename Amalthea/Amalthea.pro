include(../config.pri)

TEMPLATE = subdirs

SUBDIRS = \
    am120 \
    am200 \
    Amalthea-dso

Amalthea-dso.file = Amalthea-dso.pro

am120.file = am120/am120.pro
am200.file = am200/am200.pro
