#ifndef NODE_H
#define NODE_H
#include <QString>
#include <vector>

struct node
{
  QString name;
  std::vector <node*> nodes;

  node(QString _name)
  {
      name = _name;
  }
};

#endif // NODE_H
