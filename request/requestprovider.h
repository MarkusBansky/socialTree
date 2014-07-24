#ifndef REQUESTPROVIDER_H
#define REQUESTPROVIDER_H

#include <QObject>
#include "request.h"
#include "core/corehandler.h"
#include <QtNetwork/QTcpServer>
#include <QMap>

class RequestProvider : public QObject
{
    Q_OBJECT
public:
    explicit RequestProvider(QObject *parent = 0);
    RequestProvider(coreHandler* _coreHandler);

private:
    coreHandler* handler;
    QTcpServer* tcpServer;
    QMap<int, QTcpSocket*> SClients;
    int server_status;
    sRequest ProcessLine(QString line);
signals:

public slots:
    void onNewClient();
    void readClient();
};

#endif // REQUESTPROVIDER_H
