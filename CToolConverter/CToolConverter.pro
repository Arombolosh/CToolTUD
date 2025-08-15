TARGET = CToolConverter

TEMPLATE = app

# this pri must be sourced from all our libraries,
# it contains all functions defined for casual libraries
include( ../externals/IBK/IBK.pri )

QT = core svg

CONFIG += c++11 cmdline console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lIBK -lTiCPP -lIBKMK -lNandrad -lCToolImporter #-lVicus

INCLUDEPATH += \
    src \
    ../externals/IBK/src \
    ../externals/IBKMK/src \
    ../externals/Nandrad/src \
#    ../externals/Vicus/src \
    ../externals/TiCPP/src \
    ../externals/CToolImporter/src

DEPENDPATH = $${INCLUDEPATH}

SOURCES += \
    src/main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
