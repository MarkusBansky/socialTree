#include "corehandler.h"
#include "../request/request.h"
#define ull unsigned long long int

coreHandler::coreHandler()
{
}

void processRequest(sRequest r){
    QString name = r.name;
    QString parentName = r.parentName;
    ull timestamp = r.timestamp;
    eCommand cmd = r.cmd;


}
