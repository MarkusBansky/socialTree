#include "scenegraph.h"
#include "corehandler.h"
#include "tree.h"
#include "node.h"

std::vector<Line2F> SceneGraph::sceneLines;
std::vector<SceneNode> SceneGraph::sceneNodes;

int SceneGraph::RootChildren = 0;
int SceneGraph::FullWidth = 0;

void SceneGraph::Generator(tree* Tree){
    setCoords(Tree->root);
}

void SceneGraph::setCoords(node* leaf)
{
    size_t fullWidth = getMaxWidth(leaf);

    if (leaf->parent != NULL)
    {
        leaf->newState.y = leaf->parent->newState.y + PADDING_Y;
    } else
    {
        leaf->newState = {0, 0};
    }
    leaf->leftTime = 500;
    float gapWidth = (NODE_SIZE + PADDING_X) * fullWidth;
    float leftestCenter = leaf->newState.x - gapWidth/2.0;
    size_t processedWidth = 0;
    for (size_t i = 0; i < leaf->nodes.size(); i++)
    {
        node* child = leaf->nodes[i];
        size_t childWidth = getMaxWidth(child);
        float leftestChildCenter = leftestCenter + processedWidth*(NODE_SIZE + PADDING_X);
        float rightestChildCenter = leftestChildCenter + childWidth*(NODE_SIZE + PADDING_X);
        processedWidth += childWidth;
        child->newState.x = (leftestChildCenter + rightestChildCenter) / 2.0;
        child->leftTime = 500;
        setCoords(child);
    }
}

size_t SceneGraph::getMaxWidth(node* leaf)
{
    size_t res = 0;
    for (size_t i = 0; i < leaf->nodes.size(); i++)
        res += getMaxWidth(leaf->nodes[i]);
    return std::max(res, (size_t)1);
}
