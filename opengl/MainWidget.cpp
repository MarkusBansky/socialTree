#include "MainWidget.h"

#include <math.h>
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

MainWidget::~MainWidget()
{
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
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

    qglClearColor(Qt::black);
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

    // Reset projection
    projection.setToIdentity();
    // Set orthographic projection
    projection.ortho(0, 800, 600, 0, 0.1, 1000);
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

    //Draw test triangle
    render.setColor(0.5, 0.5, 0.5, 0.5);
    render.textureDisable();
    render.drawStart(GL_TRIANGLES);
      render.vertexAdd(0, 0, 0);
      render.vertexAdd(300, 300, 0);
      render.vertexAdd(600, 0, 0);
    render.drawStop();

    render.genVBOs();
    render.registerVBOs();
    render.drawVBOs(&program);
    render.clearVBOs();
    render.clearBuffers();
}
