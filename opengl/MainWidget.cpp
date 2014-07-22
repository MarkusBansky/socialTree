#include "MainWidget.h"

#include <cmath>
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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glLineWidth(3);

    //Enabling transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef Q_OS_WIN32
    //Enabling antialiasing for lines
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
#endif

    //Start redraw timer
    timer.start(12, this);
}

uint MainWidget::loadTexture(const QImage& image)
{
    uint id = bindTexture(image);

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return id;
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

    render.textureDisable();
    //Draw lines
    render.setColor(0.0, 0.0, 0.0, 0.4);
    render.drawStart(GL_LINES);
        for (size_t i = 0; i < SceneGraph::sceneLines.size(); i++)
        {
            render.vertexAdd(SceneGraph::sceneLines[i].start.x, SceneGraph::sceneLines[i].start.y, 1.0);
            render.vertexAdd(SceneGraph::sceneLines[i].end.x, SceneGraph::sceneLines[i].end.y, 1.0);
        }
    render.drawStop();

    //Draw nodes
//    render.setColor(0.3137254901960784, 0.5372549019607843, 0.7647058823529412, 1.0);
    render.setColor(1.0, 0.0, 0.0, 1.0);
    render.drawStart(GL_TRIANGLES);
        for (size_t i = 0; i < SceneGraph::sceneNodes.size(); i++)
        {
            const int CIRCLE_DETALIZATION = 100;
            for (int j = 0; j < CIRCLE_DETALIZATION; j++)
            {
                render.vertexAdd(SceneGraph::sceneNodes[i].center.x, SceneGraph::sceneNodes[i].center.y, 2.0);
                Vertex2F tmp;
                tmp = getCirclePoint(j, CIRCLE_DETALIZATION, SceneGraph::sceneNodes[i].center, SceneGraph::sceneNodes[i].size/2);
                render.vertexAdd(tmp.x, tmp.y, 2.0);
                tmp = getCirclePoint(j + 1, CIRCLE_DETALIZATION, SceneGraph::sceneNodes[i].center, SceneGraph::sceneNodes[i].size/2);
                render.vertexAdd(tmp.x, tmp.y, 2.0);
            }
        }
    render.drawStop();

    //Prepare data
    render.genVBOs();
    render.registerVBOs();
}

Vertex2F& MainWidget::getCirclePoint(int id, int detalization, Vertex2F& circleCenter, float radius)
{
    Vertex2F nextPoint;
    float angle = 2 * M_PI / ((float)detalization) * ((float)id);
    nextPoint.x = circleCenter.x + std::cos(angle) * radius;
    nextPoint.y = circleCenter.y + std::sin(angle) * radius;
    return nextPoint;
}
