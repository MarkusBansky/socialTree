#include "corehandler.h"
#include "../request/request.h"
#include "tree.h"
#include "scenegraph.h"
#include "../opengl/MainWidget.h"
#define ull unsigned long long int
#undef DELETE

QString gName;
QString gParentName;
ull gTimestamp;
eCommand gCmd;

tree Tree;

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

    SceneGraph::Generator(&Tree);
    //ссилка на опенджіел
    widget->updateScene();
}

void coreHandler::addCase(){
    if(this->gParentName != "NULL"){
        node* parent = Tree.search(this->gParentName);
        Tree.insert(gName, parent);
    }
    else{
        Tree.insertRoot(gName);
    }
}

void coreHandler::deleteCase(){
    Tree.deleteNode(this->gName);
}
