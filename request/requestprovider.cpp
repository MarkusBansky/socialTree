#include "requestprovider.h"
#include "core/corehandler.h"
#include <iostream>

RequestProvider::RequestProvider(QObject *parent) :
    QObject(parent)
{
    time = 0;
}

RequestProvider::RequestProvider(RequestManager *_reqManager, coreHandler* _corehandler) :
    QObject(0)
{
    time = 0;
    reqManager = _reqManager;
    handler = _corehandler;
}

void RequestProvider::onTimer() {
    time++;
    sRequest req = (*reqManager).getNextRequest(time);
    if (!req.isNull()) {
        handler->processRequest(req);
    }
}
