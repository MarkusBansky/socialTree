#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H
#include <QString>
#include "request.h"

class RequestManager {
public:
    static RequestManager* getRequestManagerInstance();
    sRequest getNextRequest(ull time);
    QString FILEPATH;
private:
    int requestIndex;
    RequestManager();
    static RequestManager* RequestManagerInstance;
    std::vector <sRequest> Requests;
    void ProcessLine(QString line);
    void ReadDb();
};

#endif // REQUESTMANAGER_H
