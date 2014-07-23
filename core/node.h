#ifndef NODE_H
#define NODE_H
#include <QString>
#include <vector>
#include "../opengl/RenderTypes.h"

struct node
{
  QString name;
  uint texture;
  std::vector <node*> nodes;
  node* parent;
  Vertex2F oldState;
  Vertex2F newState;
  float x, y;
  float leftTime;

  node(QString _name, node* _parent, uint _texture)
  {
      leftTime = 0;
      x = 0;
      y = 0;
      name = _name;
      parent = _parent;
      texture = _texture;
      if (parent != NULL)
          oldState = parent->oldState;
      else
          oldState = {0, 0};
  }
};

#endif // NODE_H
