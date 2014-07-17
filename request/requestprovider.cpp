#include "requestprovider.h"
#include <iostream>

RequestProvider::RequestProvider(QObject *parent) :
    QObject(parent)
{
    time = 0;
}

RequestProvider::RequestProvider(RequestManager *_reqManager) :
    QObject(0)
{
    time = 0;
    reqManager = _reqManager;
}

void RequestProvider::onTimer() {
    time++;
    sRequest req = (*reqManager).getNextRequest(time);
    if (!req.isNull()) {
        //TODO: add something
    }
}
