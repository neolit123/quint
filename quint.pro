QT += declarative declarative-private

rpi: DEFINES += NO_QUICKVIEW

SOURCES += main.cpp \
    codemodel.cpp \
    quintview.cpp

OTHER_FILES += \
    Fly.qml \
    Julia.qml \
    Raspberry.qml 

HEADERS += \
    codemodel.h \
    quintview.h














