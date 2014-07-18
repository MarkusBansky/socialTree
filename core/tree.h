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

        void insertRoot(QString name);
        void insert(QString name, node *leaf);
        void deleteNode(QString name);
        node *search(QString name);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        node* searchParent(QString name, node *leaf);
        node *search(QString name, node *leaf);

        node *root;
};

#endif // TREE_H
