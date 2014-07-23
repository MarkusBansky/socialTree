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
  float passedTime;
  float fullTime;

  node(QString _name, node* _parent, uint _texture)
  {
      fullTime = 1000;
      passedTime = 0;
      x = 0;
      y = 0;
      name = _name;
      parent = _parent;
      texture = _texture;
  }

  Vertex2F getCoordinates()
  {
      if (passedTime <= fullTime)
      {
          float xVector, yVector;
          xVector = newState.x - oldState.x;
          yVector = newState.y - oldState.y;
          return {
              newState.x + (passedTime/fullTime)*xVector,
              newState.y + (passedTime/fullTime)*yVector
          };
      }
      return newState;
  }
};

#endif // NODE_H
