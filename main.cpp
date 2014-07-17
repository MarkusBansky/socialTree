#include <QApplication>
#include <QTimer>
#include <QObject>

#ifndef QT_NO_OPENGL
#include <opengl/mainwidget.h>
#endif
#include "request/request.h"
#include "request/requestmanager.h"
#include "request/requestprovider.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("socialTree");
    app.setApplicationVersion("0.1");

    RequestManager* reqManager = RequestManager::getRequestManagerInstance();
    RequestProvider* reqProvider = new RequestProvider(reqManager);

    QTimer* reqTimer = new QTimer();
    reqTimer->setInterval(1000);
    reqTimer->setSingleShot(false);
    QObject::connect(reqTimer, SIGNAL(timeout()), reqProvider, SLOT(onTimer()));
    reqTimer->start();
#ifndef QT_NO_OPENGL
    MainWidget widget;
    widget.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
