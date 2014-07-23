#ifndef NODE_H
#define NODE_H
#include <QString>
#include <vector>

struct node
{
  QString name;
  uint texture;
  std::vector <node*> nodes;
  node* parent;
  float x, y;

  node(QString _name, node* _parent, uint _texture)
  {
      x = 0;
      y = 0;
      name = _name;
      parent = _parent;
      texture = _texture;
  }
};

#endif // NODE_H
