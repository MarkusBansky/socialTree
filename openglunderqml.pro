QT += core widgets opengl
QT += network

HEADERS += request/request.h \
    core/tree.h \
    core/node.h \
    core/corehandler.h \
    opengl/RenderTypes.h \
    opengl/MainWidget.h \
    opengl/VBORender.h \
    request/requestmanager.h \
    request/requestprovider.h \
    core/scenegraph.h \
    opengl/AnimationManager.h
SOURCES += main.cpp \
    core/tree.cpp \
    core/coreHandler.cpp \
    opengl/MainWidget.cpp \
    opengl/VBORender.cpp \
    request/requestmanager.cpp \
    request/requestprovider.cpp \
    core/scenegraph.cpp \
    opengl/AnimationManager.cpp
RESOURCES += opengl/shaders.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target

OTHER_FILES +=
