#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <vector>

#include "node.h"
#include "../opengl/RenderTypes.h"
#include "corehandler.h"
#include "tree.h"

const float NODE_SIZE = 60;

const float PADDING_X = 20;
const float PADDING_Y = 100;

struct SceneNode
{
    Vertex2F center;
    uint texture;
    float size;
};

class SceneGraph
{
public:
    static int RootChildren;
    static int FullWidth;

    static void Generator(tree* Tree);
    static std::vector<Line2F> sceneLines;
    static std::vector<SceneNode> sceneNodes;
private:
    static void setCoords(node* leaf);
    static size_t getMaxWidth(node* leaf);
};

#endif // SCENEGRAPH_H
