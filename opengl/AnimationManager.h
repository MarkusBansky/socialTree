#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QBasicTimer>
#include <QTimerEvent>
#include "../core/node.h"
#include "../core/corehandler.h"

class AnimationManager : public QObject
{
public:
    AnimationManager(coreHandler* core);
    ~AnimationManager();
    void timerEvent(QTimerEvent* event);
private:
    QBasicTimer animationTimer_;
    coreHandler* core_;
    bool animateNode(node* leaf);
    void updateScene(node* leaf);
};

extern AnimationManager* animationManager;

#endif // ANIMATIONMANAGER_H
