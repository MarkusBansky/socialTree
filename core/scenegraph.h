#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <vector>

#include "node.h"
#include "../opengl/RenderTypes.h"
#include "corehandler.h"
#include "tree.h"

struct SceneRectangle
{
    Vertex2F center;
    float size;
};

class SceneGraph
{
public:
    static void Generator(tree* Tree);
    static std::vector<Line2F> lines;
    static std::vector<SceneRectangle> rectangles;
private:
    static void SetCoords(node* leaf);
};

#endif // SCENEGRAPH_H
