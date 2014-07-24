#ifndef REQUEST_H
#define REQUEST_H
typedef unsigned long long int ull;
#undef DELETE

#include <vector>
#include <QString>
#include <QFile>
#include <QString>

enum eCommand {
    ADD, DELETE
};

struct sRequest {
    eCommand cmd;
    QString name;
    QString parentName;
    uint id;

    sRequest(
             eCommand _cmd,
             QString _name,
             QString _parentName)
    {
        cmd = _cmd;
        name = _name;
        parentName = _parentName;
    }

    bool isNull() {
        return
                this->cmd == ADD &&
                this->name == "" &&
                this->parentName == "";
    }

    static sRequest getNullRequest() {
        sRequest req(ADD, "", "");
        return req;
    }
};
#endif // REQUEST_H
