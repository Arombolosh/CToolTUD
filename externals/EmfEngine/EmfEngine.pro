# -----------------------------
# Project for EmfEngine library
# -----------------------------

TARGET = EmfEngine
TEMPLATE = lib

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../IBK/IBK.pri )

# Comment the line bellow if you want to disable text antialiasing
DEFINES     += HAVE_ANTIALIASED_TEXT

# Comment the line bellow if you want to be sure that the output texts will not be cropped,
# but the output text will have a smaller font size compared to what you have specified in your Qt application
DEFINES     += HAVE_FIXED_FONT_SIZE

QT += gui core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
win32 {
	LIBS    += -lgdiplus -lgdi32 -luser32 -lole32
}

HEADERS = src/EmfEngine.h
SOURCES = \
	src/EmfEnginePlus.cpp \
	src/EmfPaintDevicePlus.cpp
