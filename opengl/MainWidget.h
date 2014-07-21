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

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initTextures();

    void updateScene();
    void updateProjection();
private:
    QBasicTimer timer;
    QGLShaderProgram program;


    VBORender render;

    bool isMoving_;
    QPoint lastPos_;
    QPointF centerOffset_;


    QMatrix4x4 projection;

    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;
};

#endif // MAINWIDGET_H
