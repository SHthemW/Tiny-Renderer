#include "shape.h"

Triangle::Triangle(Vec2i p1, Vec2i p2, Vec2i p3) : _point1(p1), _point2(p2), _point3(p3) { }

Triangle::Triangle(Vec2i vertex[3]) : _point1(vertex[0]), _point2(vertex[1]), _point3(vertex[2]) {}

const bool Triangle::inside(Vec2i point) const
{
    float area = 0.5 * (-_point2.y * _point3.x + _point1.y * (-_point2.x + _point3.x) + _point1.x * (_point2.y - _point3.y) + _point2.x * _point3.y);
    float s = 1 / (2 * area) * (_point1.y * _point3.x - _point1.x * _point3.y + (_point3.y - _point1.y) * point.x + (_point1.x - _point3.x) * point.y);
    float t = 1 / (2 * area) * (_point1.x * _point2.y - _point1.y * _point2.x + (_point1.y - _point2.y) * point.x + (_point2.x - _point1.x) * point.y);

    return s > 0 && t > 0 && (1 - s - t) > 0;
}

const std::pair<Vec2i, Vec2i> Triangle::bounding_box() const
{
    int minX = std::min({ _point1.x, _point2.x, _point3.x });
    int maxX = std::max({ _point1.x, _point2.x, _point3.x });
    int minY = std::min({ _point1.y, _point2.y, _point3.y });
    int maxY = std::max({ _point1.y, _point2.y, _point3.y });

    return { Vec2i(minX, minY), Vec2i(maxX, maxY) };
}

const Vec2i Triangle::get_point1() const
{
    return _point1;
}

const Vec2i Triangle::get_point2() const
{
    return _point2;
}

const Vec2i Triangle::get_point3() const
{
    return _point3;
}
