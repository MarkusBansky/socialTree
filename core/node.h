#ifndef NODE_H
#define NODE_H
#include <QString>

struct node
{
  QString name;
  node *left;
  node *right;
};

#endif // NODE_H
