#include <QApplication>
#include <QTimer>
#include <QObject>

#ifndef QT_NO_OPENGL
#include <opengl/mainwidget.h>
#endif
#include "request/request.h"
#include "request/requestprovider.h"
#include "core/corehandler.h"
#include "opengl/AnimationManager.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Social Tree");
    app.setApplicationVersion("0.2");

#ifndef QT_NO_OPENGL
    widget = new MainWidget();
    widget->show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    coreHandler* handler = new coreHandler();
    RequestProvider* reqProvider = new RequestProvider(handler);
    animationManager = new AnimationManager(handler);
    return app.exec();
}
