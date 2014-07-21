#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <vector>

#include "node.h"
#include "../opengl/RenderTypes.h"

struct SceneRectangle
{
    Vertex2F center;
    float size;
};

class SceneGraph
{
public:
    SceneGraph();
    static std::vector<Line2F> lines;
    static std::vector<SceneRectangle> rectangles;
};

#endif // SCENEGRAPH_H
