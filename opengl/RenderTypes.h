#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include <vector>
#include <QtGlobal>

struct Vertex
{
    float x, y, z, w;
};

struct Color
{
    float r, g, b, a;
};

struct TextureCoordinates
{
    float u, v;
};

typedef std::vector<uint> ModeBuffer;
typedef std::vector<Vertex> VertexBuffer;
typedef std::vector<Color> ColorBuffer;
typedef std::vector<TextureCoordinates> TextureCoordinatesBuffer;
typedef std::vector<uint> TextureIndexBuffer;

#endif // RENDERTYPES_H
