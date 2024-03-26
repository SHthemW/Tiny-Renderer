#include "shape.h"

Triangle::Triangle(Vec2i p1, Vec2i p2, Vec2i p3) : _point1(p1), _point2(p2), _point3(p3)
{
}

bool Triangle::inside(Vec2i point)
{
    float area = 0.5 * (-_point2.y * _point3.x + _point1.y * (-_point2.x + _point3.x) + _point1.x * (_point2.y - _point3.y) + _point2.x * _point3.y);
    float s = 1 / (2 * area) * (_point1.y * _point3.x - _point1.x * _point3.y + (_point3.y - _point1.y) * point.x + (_point1.x - _point3.x) * point.y);
    float t = 1 / (2 * area) * (_point1.x * _point2.y - _point1.y * _point2.x + (_point1.y - _point2.y) * point.x + (_point2.x - _point1.x) * point.y);

    return s > 0 && t > 0 && (1 - s - t) > 0;
}

Vec2i Triangle::get_point1()
{
    return _point1;
}

Vec2i Triangle::get_point2()
{
    return _point2;
}

Vec2i Triangle::get_point3()
{
    return _point3;
}
