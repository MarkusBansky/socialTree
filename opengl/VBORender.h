#ifndef VBORENDER_H
#define VBORENDER_H

#include <vector>

#include <QtGlobal>
#include <QGLFunctions>
#include <QGLShaderProgram>

#include "RenderTypes.h"

struct VBOBuffer
{
    uint id;
    uint mode;
    uint textureIndex;
    size_t start_id, count;
};

typedef std::vector<VBOBuffer> VBOBuffers;

class VBORender : protected QGLFunctions
{
    public:
        VBORender();
        virtual ~VBORender();

        void vertexAdd(float x, float y, float z);
        void vertexAdd(const Vertex2F& pos, float z);

        void drawStart(uint mode);
        void drawStop();

        void textureEnable();
        void textureDisable();
        void textureSelect(uint index);

        void setColor(float r, float g, float b, float a);

        void setTextureCoordinates(float s, float t);
        void setTextureCoordinates(const Vertex2F& pos);

        void genVBO(size_t from, size_t to);
        void genVBOs();

        void registerVBOs();

        void drawVBOs(QGLShaderProgram* program);

        void clearVBOs();
        void clearBuffers();

        void init();
    protected:
    private:
        ModeBuffer modeBuffer_;
        VertexBuffer vertexBuffer_;
        ColorBuffer colorBuffer_;
        TextureIndexBuffer textureIndBuffer_;
        TextureCoordinatesBuffer textureCoordBuffer_;

        VBOBuffers subBuffers_;

        TextureCoordinates currentTextureCoord_;
        uint currentMode_;
        Color currentColor_;
        uint currentTexture_;
};

#endif // VBORENDER_H
