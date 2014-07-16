QT += qml quick

HEADERS += opengl/squircle.h
SOURCES += opengl/squircle.cpp main.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
