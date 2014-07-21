#include "scenegraph.h"
#include "corehandler.h"
#include "tree.h"
#include "node.h"

std::vector<Line2F> SceneGraph::lines;
std::vector<SceneRectangle> SceneGraph::rectangles;

void SceneGraph::Generator(tree* Tree){

}

void SceneGraph::SetCoords(node* leaf){
    int childCount = leaf->nodes.size();
    leaf->y = leaf->parent->y + PADDING_Y;
    int width = childCount*SQUARE_W + (childCount-1)*PADDING_X;
    int lMargin = leaf->x - width/2;

    for(int i =0; i<childCount; i++){
        leaf->nodes[i]->x = lMargin + SQUARE_W/2 + (SQUARE_W+PADDING_X)*i;
        SceneGraph::SetCoords(leaf->nodes[i]);
    }

}


