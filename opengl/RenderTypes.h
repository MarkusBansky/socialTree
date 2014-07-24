#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include <vector>
#include <QtGlobal>

struct Vertex2F
{
    float x, y;
    Vertex2F() {}
    Vertex2F(float x_, float y_)
    {
        x = x_;
        y = y_;
    }
};

struct Vertex3F
{
    float x, y, z;
    Vertex3F() {}
    Vertex3F(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};

struct Vertex4F
{
    float x, y, z, w;
    Vertex4F() {}
    Vertex4F(float x_, float y_, float z_, float w_)
    {
        x = x_;
        y = y_;
        z = z_;
        w = w_;
    }
};

struct Line2F
{
    Vertex2F start, end;
    Line2F() {}
    Line2F(Vertex2F start_, Vertex2F end_)
    {
        start = start_;
        end = end_;
    }
};

struct Line3F
{
    Vertex3F start, end;
    Line3F() {}
    Line3F(Vertex3F start_, Vertex3F end_)
    {
        start = start_;
        end = end_;
    }
};

struct Line4F
{
    Vertex4F start, end;
    Line4F() {}
    Line4F(Vertex4F start_, Vertex4F end_)
    {
        start = start_;
        end = end_;
    }
};

struct Color
{
    float r, g, b, a;
    Color() {}
    Color(float r_, float g_, float b_, float a_)
    {
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
};

struct TextureCoordinates
{
    float s, t;
    TextureCoordinates() {}
    TextureCoordinates(float s_, float t_)
    {
        s = s_;
        t = t_;
    }
};

typedef std::vector<uint> ModeBuffer;
typedef std::vector<Vertex4F> VertexBuffer;
typedef std::vector<Color> ColorBuffer;
typedef std::vector<TextureCoordinates> TextureCoordinatesBuffer;
typedef std::vector<uint> TextureIndexBuffer;

#endif // RENDERTYPES_H
