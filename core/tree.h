#ifndef TREE_H
#define TREE_H
#include "../request/request.h"
#include "node.h"
#include <QVector>
#include <QString>

class tree
{
public:
        tree();
        ~tree();

        void insert(QString name);
        node *search(QString name);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        void insert(QString name, node *leaf);
        node *search(QString name, node *leaf);

        node *root;
};

#endif // TREE_H
