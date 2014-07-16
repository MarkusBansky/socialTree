QT += qml quick

HEADERS += opengl/squircle.h \
    request/request.h \
    core/Graph.h
SOURCES += opengl/squircle.cpp main.cpp \
    request/Request.cpp \
    core/Graph.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
