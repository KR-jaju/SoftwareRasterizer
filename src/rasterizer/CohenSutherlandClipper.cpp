#include "rasterizer/CohenSutherlandClipper.hpp"


static
bool checkInPlane(Vertex &point, Vector4 &axis)
{
    _float check = point.position * axis;
    return (check <= point.position.w);
}

static
Vertex makeInterSection(Vertex &p1, Vertex &p2, Vector4 &axis)
{
    _float a0 = p1.position * axis;
    _float a1 = p2.position * axis;
    _float diff_a = a1 - a0;
    _float diff_w = p2.position.w - p1.position.w;
    _float diff_w0_a0 = p1.position.w - a0;
    _float t = diff_w0_a0 / (diff_a - diff_w);
    return Vertex::mix(p1, p2, t); 
}

static
void checkPlane(std::queue<Vertex> &out, Vector4 axis)
{
    Vertex point1, point2, intersection;
    point1 = out.front();
    out.pop();
    out.push(point1);
    if (out.size() <= 2)
        return ;
    for (int i = 0; i < int(out.size()); i++)
    {
        point2 = out.front();
        out.pop();
        if (checkInPlane(point1, axis))
        {
            out.push(point1);
            if (checkInPlane(point2, axis))
                out.push(point2);
            else
                out.push(makeInterSection(point1, point2, axis));
        }
        else
        {
            out.push(makeInterSection(point1, point2, axis));
            out.push(point2);
        }
        point1 = point2;
    }
}

void CohenSutherandClipper::clip(std::queue<Vertex> &out)
{
    checkPlane(out, Vector4(1, 0, 0, 0));
    checkPlane(out, Vector4(-1, 0, 0, 0));
    checkPlane(out, Vector4(0, 1, 0, 0));
    checkPlane(out, Vector4(0, 0, 1, 0));
    checkPlane(out ,Vector4(0, 0, -1, 0));
}