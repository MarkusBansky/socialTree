#include "scenegraph.h"
#include "corehandler.h"
#include "tree.h"
#include "node.h"

std::vector<Line2F> SceneGraph::lines;
std::vector<SceneRectangle> SceneGraph::rectangles;

int SceneGraph::RootChildren = 0;
int SceneGraph::FullWidth = 0;

void SceneGraph::Generator(tree* Tree){
    SceneGraph::lines.clear();
    SceneGraph::rectangles.clear();
    SetCoords(Tree->root);
}

void SceneGraph::SetCoords(node* leaf){
}
