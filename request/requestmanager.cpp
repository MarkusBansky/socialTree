#include "requestmanager.h"
#include "request.h"
#include <QTextStream>
#include <QStringList>
#include "../opengl/MainWidget.h"
#undef DELETE

RequestManager* RequestManager::RequestManagerInstance;

RequestManager* RequestManager::getRequestManagerInstance() {
    if (!RequestManagerInstance)
        RequestManagerInstance = new RequestManager();
    return RequestManagerInstance;
}

RequestManager::RequestManager() {
    requestIndex = 0;
    FILEPATH = "requests.dat";
    ReadDb();
}

void RequestManager::ReadDb() {
    QFile input(FILEPATH);
    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    QTextStream in(&input);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        ProcessLine(line);
    }
    input.close();
}

void RequestManager::ProcessLine(QString line) {
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
    Requests.push_back(req);
}

sRequest RequestManager::getNextRequest(ull time) {
    if (requestIndex >= Requests.size())
        return sRequest::getNullRequest();
    if (time < Requests[requestIndex].timestamp)
        return sRequest::getNullRequest();
    return Requests[requestIndex++];
}
