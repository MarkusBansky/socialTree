#include "corehandler.h"
#include "../request/request.h"
#include "tree.h"
#include "scenegraph.h"
#include "../opengl/MainWidget.h"
#include <stdexcept>
#define ull unsigned long long int
#undef DELETE

QString gName;
QString gParentName;
ull gTimestamp;
eCommand gCmd;
uint image;

tree Tree;

tree* coreHandler::getTree(){
    return &Tree;
}

void coreHandler::processRequest(sRequest r){
    gName = r.name;
    gParentName = r.parentName;
    gCmd = r.cmd;
    image = r.id;

    switch(gCmd) {
    case ADD:
        addCase();
        break;
    case DELETE:
        deleteCase();
        break;
    }

    SceneGraph::Generator(&Tree);
}

void coreHandler::addCase(){
    if(Tree.root != NULL){
        node* parent = Tree.search(this->gParentName);
        node* sameName = Tree.search(this->gName);
        if (sameName != NULL)
        {
            throw std::invalid_argument("same name");
            return;
        }
        if (parent != NULL)
            Tree.insert(gName, parent, image);
    }
    else{
        if (Tree.root != NULL)
        {
            throw std::invalid_argument("same name");
            return;
        }
        Tree.insertRoot(gName, image);
    }
}

void coreHandler::deleteCase(){
    Tree.deleteNode(this->gName);
}
