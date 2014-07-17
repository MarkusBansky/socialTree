#ifndef TREE_H
#define TREE_H
#include "../request/request.h"
#include <QVector>

class tree
{
public:
    tree();
    void processRequest(sRequest r);
private:
    void addNode();
};

#endif // TREE_H
