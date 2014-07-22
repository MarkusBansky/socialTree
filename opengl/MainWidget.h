#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QtOpenGL/QGLShaderProgram>
#include "VBORender.h"
#include "../core/scenegraph.h"


class MainWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void updateScene();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent* e);
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void resetCamera();
    void paintGL();

    void initShaders();
    uint loadTexture(const QImage& image);

    void updateProjection();
private:
    QBasicTimer timer;
    QGLShaderProgram program;


    VBORender render;

    bool isMoving_;
    QPoint lastPos_;

    QRectF sceneRect_;
    float scale_;

    QMatrix4x4 projection;
};

extern MainWidget* widget;

#endif // MAINWIDGET_H
