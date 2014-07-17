#include "request.h"
#include <QTextStream>
#include <QStringList>

RequestManager* RequestManager::RequestManagerInstance;

RequestManager* RequestManager::GetRequestManagerInstance() {
    if (!RequestManagerInstance)
        RequestManagerInstance = new RequestManager();
    return RequestManagerInstance;
}

RequestManager::RequestManager() {
    requestIndex = 0;
}

void RequestManager::ReadDb() {
    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    QTextStream in(&input);
    QString line;
    while (!in.atEnd()) {
        line = in.readLine();
        ProcessLine(line);
    }
}

void RequestManager::ProcessLine(QString line) {
    QStringList requestList = line.split(" ", QString::SkipEmptyParts);
    QString timestampString = requestList.at(0);
    QString cmdString = requestList.at(1);
    QString nameString = requestList.at(2);
    QString parentNameString = "";
    if (requestList.size() == 4)
        parentNameString = requestList.at(3);
    sRequest req = sRequest::getNullRequest();
    req.timestamp = timestampString.toInt();
    if (cmdString == "ADD")
        req.cmd = ADD;
    else
        req.cmd = DELETE;
    req.name = nameString;
    req.parentName = parentNameString;
    Requests.push_back(req);
}

sRequest RequestManager::getNextRequest(ull time) {
    if (requestIndex >= Requests.size())
        return sRequest(0, ADD, "", "");
    if (time >= Requests[requestIndex].timestamp)
        return sRequest(0, ADD, "", "");
    return Requests[requestIndex++];
}
