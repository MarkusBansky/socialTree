#include "requestprovider.h"
#include "core/corehandler.h"
#include <iostream>
#include <QTcpSocket>
#include <QDateTime>

RequestProvider::RequestProvider(QObject *parent) :
    QObject(parent)
{
    time = 0;
}

RequestProvider::RequestProvider(RequestManager *_reqManager, coreHandler* _corehandler) :
    QObject(0)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewClient()));
    if (!tcpServer->listen(QHostAddress::Any, 4747) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << QString::fromUtf8("Server Started");
    }
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

void RequestProvider::onNewClient() {
    if(server_status==1){
        qDebug() << QString::fromUtf8("new connection");
        QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        SClients[idusersocs]=clientSocket;
        connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(readClient()));
    }

}

void RequestProvider::readClient() {
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << "HTTP/1.0 200 Ok\r\n"
          "Content-Type: text/html; charset=\"utf-8\"\r\n"
          "\r\n"
          "<h1>Nothing to see here</h1>\n"
    << QDateTime::currentDateTime().toString() << "\n";
    QString temp;
    while (clientSocket->bytesAvailable())
    {
        temp = clientSocket->readAll();
        qDebug() << temp;
    }
    clientSocket->close();
    SClients.remove(idusersocs);
}
