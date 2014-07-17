#ifndef TREE_H
#define TREE_H
#include "../request/request.h"
#include "node.h"
#include <QVector>

class tree
{
public:
        tree();
        ~tree();

        void insert(int key);
        node *search(int key);
        void destroy_tree();

    private:
        void destroy_tree(node *leaf);
        void insert(int key, node *leaf);
        node *search(int key, node *leaf);

        node *root;
};

#endif // TREE_H
