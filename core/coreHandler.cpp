#include "corehandler.h"
#include "../request/request.h"
#include "tree.h"
#define ull unsigned long long int

QString gName;
QString gParentName;
ull gTimestamp;
eCommand gCmd;

void coreHandler::processRequest(sRequest r){
    gName = r.name;
    gParentName = r.parentName;
    gTimestamp = r.timestamp;
    gCmd = r.cmd;

    switch(gCmd) {
    case ADD:
        addCase();
        break;
    case DELETE:
        deleteCase();
        break;
    }
}

void coreHandler::addCase(){
    //search for parrent
    //int key = tree.strSearch(qParentName);
}

void coreHandler::deleteCase(){


}
