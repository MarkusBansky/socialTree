#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include <vector>
#include <QtGlobal>

struct Line2F
{
    Vertex2F start, end;
};

struct Line3F
{
    Vertex2F start, end;
};

struct Line4F
{
    Vertex2F start, end;
};

struct Vertex2F
{
    float x, y;
};

struct Vertex3F
{
    float x, y, z;
};

struct Vertex4F
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
typedef std::vector<Vertex4F> VertexBuffer;
typedef std::vector<Color> ColorBuffer;
typedef std::vector<TextureCoordinates> TextureCoordinatesBuffer;
typedef std::vector<uint> TextureIndexBuffer;

#endif // RENDERTYPES_H
