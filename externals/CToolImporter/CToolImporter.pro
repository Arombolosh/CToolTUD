# -------------------------------------------------
# Project for CToolImporter data model library
# -------------------------------------------------
TARGET = CToolImporter
TEMPLATE = lib

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../IBK/IBK.pri )


QT += core

unix|mac {
	VER_MAJ = 0
	VER_MIN = 1
	VER_PAT = 0
	VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}
}

 LIBS += -lIBK -lIBKMK -lNandrad -lTiCPP #-lDataIO -lCCM -lglm -lVicus

INCLUDEPATH = \
	src \
	../IBK/src \
	#../glm/src \
	../IBKMK/src \
	../Nandrad/src \
	#../DataIO/src \
	#../CCM/src \
	#../Vicus/src \
	../TiCPP/src

DEPENDPATH = $${INCLUDEPATH}

HEADERS += \
	src/CTI_Project.h \
	src/CTI_Room.h \
	src/CTI_Surface.h

SOURCES += \
	src/CTI_Project.cpp \
	src/CTI_Room.cpp \
	src/CTI_Surface.cpp

