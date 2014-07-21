#ifndef NODE_H
#define NODE_H
#include <QString>
#include <vector>

struct node
{
  QString name;
  std::vector <node*> nodes;
  node* parent;

  node(QString _name, node* _parent)
  {
      name = _name;
      parent = _parent;
  }
};

#endif // NODE_H
