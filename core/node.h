#ifndef NODE_H
#define NODE_H
#include <QString>
#include <vector>

struct node
{
  QString name;
  std::vector <node*> nodes;
  node* parent;
  float x, y;

  node(QString _name, node* _parent)
  {
      x = 0;
      y = 0;
      name = _name;
      parent = _parent;
  }
};

#endif // NODE_H
