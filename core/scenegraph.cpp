#include "scenegraph.h"
#include "corehandler.h"
#include "tree.h"
#include "node.h"

std::vector<Line2F> SceneGraph::sceneLines;
std::vector<SceneNode> SceneGraph::sceneNodes;

int SceneGraph::RootChildren = 0;
int SceneGraph::FullWidth = 0;

void SceneGraph::Generator(tree* Tree){
    SceneGraph::sceneLines.clear();
    SceneGraph::sceneNodes.clear();
    setCoords(Tree->root);
}

void SceneGraph::setCoords(node* leaf)
{
    size_t fullWidth = getMaxWidth(leaf);

    if (leaf->parent != NULL)
    {
        leaf->y = leaf->parent->y + PADDING_Y;
    } else
    {
        leaf->x = 0;
        leaf->y = 0;
    }
    leaf->newState = ({leaf->x, leaf->y});
    //sceneNodes.push_back({{leaf->x, leaf->y}, leaf->texture, NODE_SIZE});
    float gapWidth = (NODE_SIZE + PADDING_X) * fullWidth;
    float leftestCenter = leaf->x - gapWidth/2.0;
    size_t processedWidth = 0;
    for (size_t i = 0; i < leaf->nodes.size(); i++)
    {
        node* child = leaf->nodes[i];
        size_t childWidth = getMaxWidth(child);
        float leftestChildCenter = leftestCenter + processedWidth*(NODE_SIZE + PADDING_X);
        float rightestChildCenter = leftestChildCenter + childWidth*(NODE_SIZE + PADDING_X);
        processedWidth += childWidth;
        child->x = (leftestChildCenter + rightestChildCenter) / 2.0;
        setCoords(child);
        //sceneLines.push_back({{leaf->x,  leaf->y + NODE_SIZE/2},{child->x, child->y - NODE_SIZE/2}});
    }
}

size_t SceneGraph::getMaxWidth(node* leaf)
{
    size_t res = 0;
    for (size_t i = 0; i < leaf->nodes.size(); i++)
        res += getMaxWidth(leaf->nodes[i]);
    return std::max(res, (size_t)1);
}
