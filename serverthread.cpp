#include "serverthread.h"
#include "request/requestmanager.h"
#include "core/corehandler.h"

#include <QtNetwork>

ServerThread::ServerThread(int socketDescriptor, QObject *parent, coreHandler* _handler):QThread(parent), socketDescriptor(socketDescriptor)
{
    handler = _handler;
}

void ServerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << text;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QByteArray bytes = tcpSocket.readAll();
    text = QTextCodec::codecForMib(1015)->toUnicode(bytes);
    RequestManager* reqManager = RequestManager::getRequestManagerInstance();
    handler->processRequest(reqManager->ProcessLine(text));

    tcpSocket.write(block);
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
