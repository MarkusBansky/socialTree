#include "MainWidget.h"

#include <math.h>
#include <QMouseEvent>

MainWidget* widget;

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{
    resetCamera();
}

MainWidget::~MainWidget()
{
    //Clear render data
    render.clearVBOs();
    render.clearBuffers();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        isMoving_ = true;
        lastPos_ = e->pos();
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    switch (e->button()) {
    case Qt::LeftButton:
        isMoving_ = false;
        break;
    case Qt::MiddleButton:
        resetCamera();
        updateProjection();
        break;
    default:
        break;
    }
    updateScene();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (isMoving_)
    {
        QPointF delta = e->pos() - lastPos_;
        sceneRect_.translate(-(delta/scale_));
        lastPos_ = e->pos();
        updateProjection();
    }
}

void MainWidget::wheelEvent(QWheelEvent* e)
{
    const float SCALING_SPEED = 1.001;
    float coef = pow(SCALING_SPEED, e->delta());

    //Getting scene coordinates of current screen center
    QPointF center = QPointF(sceneRect_.left() + e->x()/scale_, sceneRect_.top() + e->y()/scale_);

    scale_ *= coef;

    //Recalculating rect
    sceneRect_.setLeft(center.x() - e->x()/scale_);
    sceneRect_.setRight(center.x() + (width() - e->x())/scale_);
    sceneRect_.setTop(center.y() - e->y()/scale_);
    sceneRect_.setBottom(center.y() + (height() - e->y())/scale_);

    updateProjection();
}

void MainWidget::timerEvent(QTimerEvent *)
{
    updateGL();
}

void MainWidget::initializeGL()
{
    initializeGLFunctions();
    render.init();

    initShaders();

    qglClearColor(Qt::white);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    //Enabling transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enabling antialiasing for lines
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    //Start redraw timer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    // Compile shaders
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

void MainWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    //Scale rect
    sceneRect_.setSize(QSizeF(w/scale_, h/scale_));

    updateProjection();
}

void MainWidget::resetCamera()
{
    const int TOP_OFFSET = 100;
    //Init camera rect where scene(0, 0) points to screen (width/2, -TOP_OFFSET)
    sceneRect_ = QRectF(-width()/2, -TOP_OFFSET, width(), height());
    scale_ = 1.0;
}

void MainWidget::updateProjection()
{
    // Reset projection
    projection.setToIdentity();
    // Set orthographic projection
    projection.ortho(sceneRect_.left(), sceneRect_.right(), sceneRect_.bottom(), sceneRect_.top(), 0.1, 10000);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view matrix
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -1000.0);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    render.drawVBOs(&program);
}

void MainWidget::updateScene()
{
    //Clear previous data
    render.clearVBOs();
    render.clearBuffers();

    //Draw lines
    render.setColor(0.0, 0.0, 1.0, 1.0);
    render.drawStart(GL_LINES);
        for (size_t i = 0; i < SceneGraph::lines.size(); i++)
        {
            render.vertexAdd(SceneGraph::lines[i].start.x, SceneGraph::lines[i].start.y, 1.0);
            render.vertexAdd(SceneGraph::lines[i].end.x, SceneGraph::lines[i].end.y, 1.0);
        }
    render.drawStop();

    //Draw rectangles
    render.setColor(1.0, 0.0, 0.0, 1.0);
    render.drawStart(GL_TRIANGLES);
        for (size_t i = 0; i < SceneGraph::rectangles.size(); i++)
        {
            render.vertexAdd(SceneGraph::rectangles[i].center.x - SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0); //left top
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0); //right top
            render.vertexAdd(SceneGraph::rectangles[i].center.x - SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0); //left bottom
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0); //right top
            render.vertexAdd(SceneGraph::rectangles[i].center.x - SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0); //left bottom
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0); //right bottom
        }
    render.drawStop();

    //Prepare data
    render.genVBOs();
    render.registerVBOs();
}
