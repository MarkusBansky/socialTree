#include "corehandler.h"
#include "../request/request.h"
#include "tree.h"
#define ull unsigned long long int

QString gName;
QString gParentName;
ull gTimestamp;
eCommand gCmd;

tree Tree = tree();

tree coreHandler::getTree(){
    return Tree;
}

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
    node* parent = Tree .strSearch(gParentName);
    int key = parent->key_value;
}

void coreHandler::deleteCase(){


}
