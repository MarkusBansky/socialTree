#include "scenegraph.h"
#include "corehandler.h"
#include "tree.h"
#include "node.h"

std::vector<Line2F> SceneGraph::lines;
std::vector<SceneRectangle> SceneGraph::rectangles;

void SceneGraph::Generator(tree* Tree){
    SceneGraph::lines.clear();
    SceneGraph::rectangles.clear();
    SetCoords(Tree->root);
}

void SceneGraph::SetCoords(node* leaf){
    int childCount = leaf->nodes.size();
    if (leaf->parent != NULL)
        leaf->y = leaf->parent->y + PADDING_Y;
    int width = childCount*SQUARE_W + (childCount-1)*PADDING_X;
    int lMargin = leaf->x - width/2;
    if (leaf->parent != NULL)
        lines.push_back({{leaf->parent->x, leaf->parent->y},
                                         {leaf->x, leaf->y}});
    rectangles.push_back({{leaf->x, leaf->y}, SQUARE_W*1.0f});
    for(int i =0; i<childCount; i++){
        leaf->nodes[i]->x = lMargin + SQUARE_W/2 + (SQUARE_W+PADDING_X)*i;
        SetCoords(leaf->nodes[i]);
    }

}


