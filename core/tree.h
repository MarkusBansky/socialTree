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

        void insert(int key);
        node *search(int key);
        node *strSearch(QString name);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);
        node *strSearch(QString name, node *leaf);

        node *root;
};

#endif // TREE_H
