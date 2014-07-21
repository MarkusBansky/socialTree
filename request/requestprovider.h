#ifndef REQUESTPROVIDER_H
#define REQUESTPROVIDER_H

#include <QObject>
#include "requestmanager.h"
#include "request.h"
#include "core/corehandler.h"

class RequestProvider : public QObject
{
    Q_OBJECT
public:
    explicit RequestProvider(QObject *parent = 0);
    RequestProvider(RequestManager* _reqManager, coreHandler* _coreHandler);

private:
    ull time;
    RequestManager* reqManager;
    coreHandler* handler;
signals:

public slots:
    void onTimer();
};

#endif // REQUESTPROVIDER_H
