#include "MainWidget.h"

#include <math.h>
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{
    centerOffset_ = QPointF(0.0, 0.0);
    scale_ = 1.0;
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
    default:
//        SceneGraph::lines.push_back({{0, }, {qrand()%800 - 400, qrand()%600 - 300}});
        SceneGraph::lines.push_back({{0, 0}, {0, 10000}});
        SceneGraph::lines.push_back({{0, 0}, {10000, 0}});
        SceneGraph::rectangles.push_back({{0, 0}, 60});
        SceneGraph::rectangles.push_back({{0, 100}, 60});
        SceneGraph::rectangles.push_back({{100, 100}, 60});
//        SceneGraph::lines.push_back({{qrand()%800 - 400, qrand()%600 - 300}, {qrand()%800 - 400, qrand()%600 - 300}});
//        SceneGraph::rectangles.push_back({{qrand()%800 - 400, qrand()%600 - 300}, qrand()%50 + 50});
        break;
    }
    updateScene();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (isMoving_)
    {
        QPointF delta = (lastPos_ - e->pos())/scale_;
        centerOffset_ += delta;
        lastPos_ = e->pos();
        updateProjection();
    }
}

void MainWidget::wheelEvent(QWheelEvent* e)
{
    float coef = pow(SCALING_SPEED, e->delta());
    scale_ *= coef;
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

    updateProjection();
}

void MainWidget::updateProjection()
{
    const int TOP_OFFSET = 100;
    // Reset projection
    projection.setToIdentity();
    // Set orthographic projection, where scene (0, 0) is at window (window.width/2, TOP_OFFSET)
    projection.ortho((-DEFAULT_WINDOW_WIDTH/2  + centerOffset_.x()) / scale_,
                      (DEFAULT_WINDOW_WIDTH/2  + centerOffset_.x()) / scale_,
                     (-TOP_OFFSET + DEFAULT_WINDOW_HEIGHT + centerOffset_.y()) / scale_,
                     (-TOP_OFFSET + centerOffset_.y()) / scale_, 0.1, 1000);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view matrix
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -100.0);

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
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0);
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0);
            render.vertexAdd(SceneGraph::rectangles[i].center.x - SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0);
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y - SceneGraph::rectangles[i].size/2, 2.0);
            render.vertexAdd(SceneGraph::rectangles[i].center.x - SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0);
            render.vertexAdd(SceneGraph::rectangles[i].center.x + SceneGraph::rectangles[i].size/2,
                             SceneGraph::rectangles[i].center.y + SceneGraph::rectangles[i].size/2, 2.0);
        }
    render.drawStop();

    //Prepare data
    render.genVBOs();
    render.registerVBOs();
}
