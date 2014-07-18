#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include "node.h"

class SceneGraph
{
public:
    SceneGraph();
private:
    int levelD;
    int dA;

    void GenerateRectangleCoordinates(node* Node);
};

#endif // SCENEGRAPH_H
