#ifndef REQUEST_H
#define REQUEST_H
#define ull unsigned long long int

#include <vector>
#include <QString>
#include <QFile>

enum eCommand {
    ADD,
    DELETE
};

struct sRequest {
    ull timestamp;
    eCommand cmd;
    QString name;
    QString parentName;
};

class RequestManager {
public:
    static RequestManager* GetRequestManagerInstance();
    const QString FILEPATH = "requests.dat";
private:
    RequestManager();
    RequestManager* RequestManagerInstance;
    std::vector <sRequest> Requests;
    QFile input;
};

#endif // REQUEST_H
