#include "requestprovider.h"
#include "core/corehandler.h"
#include <iostream>
#include <QTcpSocket>
#include <QDateTime>
#include "../opengl/MainWidget.h"
#undef DELETE

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
    os << "Connection established"
    << QDateTime::currentDateTime().toString() << "\n";
    QString temp;
    while (clientSocket->bytesAvailable())
    {
        temp = clientSocket->readAll();
        qDebug() << temp;
    }
    sRequest req = ProcessLine(temp);
    handler->processRequest(req);
    clientSocket->close();
    SClients.remove(idusersocs);
}

sRequest RequestProvider::ProcessLine(QString line) {
    QStringList requestList = line.split(" ", QString::SkipEmptyParts);
    QString timestampString = requestList.at(0);
    QString cmdString = requestList.at(1);
    QString nameString = requestList.at(2);
    QString parentNameString = "";
    QString filePath = "";
    if (requestList.size() >= 4) {
        parentNameString = requestList.at(3);
        filePath = requestList.at(4);
    }
    sRequest req = sRequest::getNullRequest();
    req.timestamp = timestampString.toInt();
    if (cmdString == "ADD")
        req.cmd = ADD;
    else
        req.cmd = DELETE;
    req.name = nameString;
    req.parentName = parentNameString;
    QImage image(filePath);
    req.id = widget->loadTexture(image);
    return req;
}
