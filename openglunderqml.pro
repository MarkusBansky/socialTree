QT += qml quick

HEADERS += opengl/squircle.h \
    core/addelement.h \
    request/request.h
SOURCES += opengl/squircle.cpp main.cpp \
    core/addelement.cpp \
    request/Request.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
