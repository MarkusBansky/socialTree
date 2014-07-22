#include "VBORender.h"

#include <algorithm>
#include <vector>

VBORender::VBORender()
{
    currentMode_ = -1;
    currentColor_ = {1, 1, 1, 1};
    currentTexture_ = 0;
    currentTextureCoord_ = {0, 0};
}

VBORender::~VBORender()
{
}

void VBORender::vertexAdd(float x, float y, float z)
{
    modeBuffer_.push_back(currentMode_);
    Vertex4F vertex = {x, y, z, 1.0};
    vertexBuffer_.push_back(vertex);
    colorBuffer_.push_back(currentColor_);
    textureIndBuffer_.push_back(currentTexture_);
    textureCoordBuffer_.push_back(currentTextureCoord_);
}

void VBORender::drawStart(uint mode)
{
    currentMode_ = mode;
}

void VBORender::drawStop()
{
    currentMode_ = -1;
}

void VBORender::textureEnable()
{
}

void VBORender::textureDisable()
{
    currentTexture_ = 0;
}

void VBORender::textureSelect(uint index)
{
    currentTexture_ = index;
}

void VBORender::setColor(float r, float g, float b, float a)
{
    currentColor_ = {r, g, b, a};
}

void VBORender::setTextureCoordinates(float s, float t)
{
    currentTextureCoord_ = {s, t};
}

void VBORender::genVBO(size_t from, size_t to)
{
    VBOBuffer tmp;
    tmp.mode = modeBuffer_[from];
    tmp.textureIndex = textureIndBuffer_[from];
    tmp.count = to - from + 1;
    tmp.start_id = from;
    subBuffers_.push_back(tmp);
}

void VBORender::genVBOs()
{
    if (modeBuffer_.empty()) return;
    size_t start = 0;
    uint modeInd = modeBuffer_[0];
    uint textureInd = textureIndBuffer_[0];
    for (size_t i = 1; i < modeBuffer_.size(); i++)
    {
        if ((modeBuffer_[i] != modeInd) || (textureIndBuffer_[i] != textureInd))
        {
            genVBO(start, i - 1);
            start = i;
            modeInd = modeBuffer_[i];
            textureInd = textureIndBuffer_[i];
        }
    }
    genVBO(start, modeBuffer_.size() - 1);
}

void VBORender::registerVBOs()
{
    for (size_t i = 0; i < subBuffers_.size(); i++)
    {
        size_t vSize = sizeof(Vertex4F)*subBuffers_[i].count,
               cSize = sizeof(Color)*subBuffers_[i].count,
               tSize = sizeof(TextureCoordinates)*subBuffers_[i].count;

        glGenBuffers(1, &(subBuffers_[i].id));

        glBindBuffer(GL_ARRAY_BUFFER, subBuffers_[i].id);
        glBufferData(GL_ARRAY_BUFFER, vSize + cSize + tSize, 0, GL_STATIC_DRAW);

        glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, &(vertexBuffer_[subBuffers_[i].start_id]));
        glBufferSubData(GL_ARRAY_BUFFER, vSize, cSize, &(colorBuffer_[subBuffers_[i].start_id]));
        glBufferSubData(GL_ARRAY_BUFFER, vSize + cSize, tSize, &(textureCoordBuffer_[subBuffers_[i].start_id]));

        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
}

void VBORender::drawVBOs(QGLShaderProgram* program)
{
    for (size_t i = 0; i < subBuffers_.size(); i++)
    {
        size_t vSize = sizeof(Vertex4F)*subBuffers_[i].count,
               cSize = sizeof(Color)*subBuffers_[i].count,
               tSize = sizeof(TextureCoordinates)*subBuffers_[i].count;

        glBindTexture(GL_TEXTURE_2D, subBuffers_[i].textureIndex);

        program->setUniformValue("hasTexture", subBuffers_[i].textureIndex > 0);
        program->setUniformValue("textureSample", 0);

        glBindBuffer(GL_ARRAY_BUFFER, subBuffers_[i].id);

        int vertexLocation = program->attributeLocation("position");
        program->enableAttributeArray(vertexLocation);
        glVertexAttribPointer(vertexLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        int colorLocation = program->attributeLocation("color");
        program->enableAttributeArray(colorLocation);
        glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (const void *)vSize);

        int texcoordLocation = program->attributeLocation("texcoord");
        program->enableAttributeArray(texcoordLocation);
        glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (const void *)(vSize + cSize));

        glDrawArrays(subBuffers_[i].mode, 0, subBuffers_[i].count);

        program->disableAttributeArray(texcoordLocation);
        program->disableAttributeArray(colorLocation);
        program->disableAttributeArray(vertexLocation);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBORender::clearVBOs()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (size_t i = 0; i < subBuffers_.size(); i++)
        glDeleteBuffers(1, &(subBuffers_[i].id));
    subBuffers_.clear();
}

void VBORender::clearBuffers()
{
    modeBuffer_.clear();
    vertexBuffer_.clear();
    colorBuffer_.clear();
    textureIndBuffer_.clear();
    textureCoordBuffer_.clear();
    //Force releasing memory
    ModeBuffer().swap(modeBuffer_);
    VertexBuffer().swap(vertexBuffer_);
    ColorBuffer().swap(colorBuffer_);
    TextureIndexBuffer().swap(textureIndBuffer_);
    TextureCoordinatesBuffer().swap(textureCoordBuffer_);
}

void VBORender::init()
{
    initializeGLFunctions();
}
