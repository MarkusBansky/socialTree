#include "AnimationManager.h"
#include "../core/scenegraph.h"
#include "MainWidget.h"

AnimationManager* animationManager;

AnimationManager::AnimationManager(coreHandler* core)
{
    animationTimer_.start(10, this);
    core_ = core;
}

AnimationManager::~AnimationManager()
{
    animationTimer_.stop();
}

void AnimationManager::timerEvent(QTimerEvent* event)
{
    if (core_->getTree()->root != NULL)
    {
        if (animateNode(core_->getTree()->root))
        {
            SceneGraph::sceneLines.clear();
            SceneGraph::sceneNodes.clear();
            updateScene(core_->getTree()->root);
            widget->updateScene();
        }
    } else {
        if (!(SceneGraph::sceneNodes.empty() && SceneGraph::sceneLines.empty()))
        {
            SceneGraph::sceneLines.clear();
            SceneGraph::sceneNodes.clear();
            widget->updateScene();
        }
    }
}

bool AnimationManager::animateNode(node* leaf)
{
    bool somethingChanged = false;
    if (leaf->leftTime > 0.0)
    {
        leaf->oldState.x += (leaf->newState.x - leaf->oldState.x)*(10.0/leaf->leftTime);
        leaf->oldState.y += (leaf->newState.y - leaf->oldState.y)*(10.0/leaf->leftTime);
        leaf->leftTime -= 10.0;
        somethingChanged = true;
    }
    for (size_t i = 0; i < leaf->nodes.size(); i++)
    {
        if (animateNode(leaf->nodes[i]))
            somethingChanged = true;
    }
    return somethingChanged;
}

void AnimationManager::updateScene(node* leaf)
{
    SceneGraph::sceneNodes.push_back(SceneNode(Vertex2F(leaf->oldState.x, leaf->oldState.y), leaf->texture, NODE_SIZE));
    for (size_t i = 0; i < leaf->nodes.size(); i++)
    {
        node* child = leaf->nodes[i];
        SceneGraph::sceneLines.push_back(Line2F(Vertex2F(leaf->oldState.x, leaf->oldState.y + NODE_SIZE/2) , Vertex2F(child->oldState.x, child->oldState.y - NODE_SIZE/2)));
        updateScene(leaf->nodes[i]);
    }
}
