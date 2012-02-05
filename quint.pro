QT += declarative declarative-private quick

rpi: DEFINES += NO_QUICKVIEW

SOURCES += main.cpp \
    codemodel.cpp \
    quintview.cpp

OTHER_FILES += \
    quint.qml \
    HelloWorld.qml \
    Fly.qml \
    Julia.qml \
    Raspberry.qml \ 
    VideoFx.qml \
    Scratchpad.qml

HEADERS += \
    codemodel.h \
    quintview.h

QML_FILE_LINKS =
for(FILE,OTHER_FILES){
    QML_FILE_LINKS += $${_PRO_FILE_PWD_}/$${FILE}
    QMAKE_POST_LINK += $$quote(cp $${_PRO_FILE_PWD_}/$${FILE} $${OUT_PWD}$$escape_expand(\n\t))
}

POST_TARGETDEPS += $${QML_FILE_LINKS}









