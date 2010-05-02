TEMPLATE = lib 

TARGET = ../lib/fcgiio

include(../../config.pri)
linux {
DEPENDPATH += . inc src \
              ../json ../json/inc ../json/src \
              ../common ../common/inc \
              ../common/common ../common/common/inc ../common/common/src \
              ../common/exception ../common/exception/inc \
              ../common/thread ../common/thread/inc

INCLUDEPATH += . inc \
               ../json/inc \
               ../common/inc \
               ../common/common/inc \
               ../common/exception/inc \
               ../common/thread/inc

# Input
HEADERS += inc/ChannelList.h \
           inc/stream.h \

SOURCES += src/ChannelList.cpp \
           src/stream.cpp 

LIBS +=  -lfcgi -lcommon 
}
OBJECTS_DIR = .obj
MOC_DIR = .moc
