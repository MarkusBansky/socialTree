QT += qml quick

HEADERS += opengl/squircle.h \
    core/addelement.h
SOURCES += opengl/squircle.cpp main.cpp \
    core/addelement.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target
