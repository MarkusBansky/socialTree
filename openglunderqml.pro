QT += qml quick

HEADERS += opengl/squircle.h \
    request/request.h \
    core/tree.h \
    core/node.h \
    core/corehandler.h
SOURCES += opengl/squircle.cpp main.cpp \
    request/Request.cpp \
    core/tree.cpp \
    core/node.cpp \
    core/coreHandler.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
