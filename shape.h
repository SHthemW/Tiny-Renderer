#include "geometry.h"


template<class T> struct Triangle
{
protected:
	T _point1;
	T _point2;
	T _point3;

	Triangle(T p1, T p2, T p3) : _point1(p1), _point2(p2), _point3(p3)
	{ }

	Triangle(T vertex[3]) : _point1(vertex[0]), _point2(vertex[1]), _point3(vertex[2])
	{ }

public:
	const T get_point1() const
	{
		return _point1;
	}

	const T get_point2() const
	{
		return _point2;
	}

	const T get_point3() const
	{
		return _point3;
	}

	const Vec3f barycenter() const
	{
		return Vec3f(
			(_point1.x + _point2.x + _point3.x) / 3.0f, 
			(_point1.y + _point2.y + _point3.y) / 3.0f, 
			(_point1.z + _point2.z + _point3.z) / 3.0f);
	}

	const static Vec3f calc_normal(Vec3f a, Vec3f b)
	{
		return a ^ b;
	}
};

struct Triangle2D : public Triangle<Vec2i>
{
public:
	Triangle2D(Vec2i p1, Vec2i p2, Vec2i p3) : Triangle<Vec2i>(p1, p2, p3)
	{ }

	Triangle2D(Vec2i vertex[3]) : Triangle<Vec2i>(vertex)
	{ }

	const bool inside(Vec2i point) const
	{
		float area = 0.5 * (-_point2.y * _point3.x + _point1.y * (-_point2.x + _point3.x) + _point1.x * (_point2.y - _point3.y) + _point2.x * _point3.y);
		float s = 1 / (2 * area) * (_point1.y * _point3.x - _point1.x * _point3.y + (_point3.y - _point1.y) * point.x + (_point1.x - _point3.x) * point.y);
		float t = 1 / (2 * area) * (_point1.x * _point2.y - _point1.y * _point2.x + (_point1.y - _point2.y) * point.x + (_point2.x - _point1.x) * point.y);

		return s > 0 && t > 0 && (1 - s - t) > 0;
	}

	const std::pair<Vec2i, Vec2i> bounding_box() const
	{
		int minX = std::min({ _point1.x, _point2.x, _point3.x });
		int maxX = std::max({ _point1.x, _point2.x, _point3.x });
		int minY = std::min({ _point1.y, _point2.y, _point3.y });
		int maxY = std::max({ _point1.y, _point2.y, _point3.y });

		return { Vec2i(minX, minY), Vec2i(maxX, maxY) };
	}
};

struct Triangle3D : public Triangle<Vec3f>
{
public:
	Triangle3D(Vec3f p1, Vec3f p2, Vec3f p3) : Triangle<Vec3f>(p1, p2, p3)
	{ }

	Triangle3D(Vec3f vertex[3]) : Triangle<Vec3f>(vertex)
	{ }

	const Vec3f normal() const
	{
		Vec3f edge1 = _point3 - _point1;
        Vec3f edge2 = _point2 - _point1; // dont change the order!
        return edge1 ^ edge2;
	}
};