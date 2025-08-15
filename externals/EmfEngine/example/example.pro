TARGET         = example
TEMPLATE       = app
CONFIG        += warn_on release console

MOC_DIR      = ../tmp
OBJECTS_DIR  = ../tmp
DESTDIR      = ../

contains(QT_VERSION, ^5.*){
	QT += widgets
}

INCLUDEPATH   += ../src

contains(CONFIG, EmfEngineDll){
	LIBS   += ../EmfEngine.dll
} else {
	LIBS   += ../EmfEngine.lib
}
LIBS   += -lgdiplus -lgdi32 -luser32 -lole32

HEADERS       = renderarea.h \
                pixmaps.h
SOURCES       = main.cpp \
                renderarea.cpp