QT += qml quick

HEADERS += opengl/squircle.h \
    request/request.h \
    core/tree.h \
    core/node.h
SOURCES += opengl/squircle.cpp main.cpp \
    request/Request.cpp \
    core/tree.cpp \
    core/node.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
