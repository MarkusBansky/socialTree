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
    SetChildCount(Tree->root);

    RootChildren = Tree->root->Childs;
    FullWidth = RootChildren*SQUARE_W + (RootChildren-1)*PADDING_X;

    CheckCollisions(Tree->root);
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

void SceneGraph::SetChildCount(node *leaf){
    for(int i = 0; i<leaf->nodes.size(); i++){
        SetChildCount(leaf->nodes[i]);
    }
    if(leaf->parent != NULL)
        leaf->Childs++;
}

<<<<<<< HEAD
void SceneGraph::CheckCollisions(node *leaf){
    for(int i = 0; i<leaf->nodes.size(); i++){
        CheckCollisions(leaf->nodes[i]);
    }
    if(leaf->Childs != 0 && leaf->parent != NULL){
        int partition = FullWidth*(leaf->Childs+1)/RootChildren;
        int offset = 0;
        if(leaf->x < 0)
            offset = -(partition/2-SQUARE_W/2);
        if(leaf->x > 0)
            offset = (partition/2-SQUARE_W/2);
        SetOffset(leaf, offset);
    }
}

void SceneGraph::SetOffset(node *leaf, int offset){
    leaf->x = leaf->x + offset;
=======
    int offset = myX - parentX;
    if(offset!=0 && leaf->parent != NULL)
        SceneGraph::SetOffset(leaf->parent, offset);
}

void SceneGraph::SetOffset(node *leaf, int offset){
    if(leaf->parent != NULL)
        leaf->x = leaf->x - offset;
>>>>>>> origin/master
    for(int i = 0; i<leaf->nodes.size(); i++){
        SetOffset(leaf->nodes[i], offset);
    }
}
