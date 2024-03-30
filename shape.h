#include "geometry.h"


class Triangle 
{
private:
	Vec2i _point1;
	Vec2i _point2;
	Vec2i _point3;

public:
	Triangle(Vec2i p1, Vec2i p2, Vec2i p3);
	Triangle(Vec2i vertex[3]);

	const bool inside(Vec2i point) const;
	const std::pair<Vec2i, Vec2i> bounding_box() const;

	const Vec2i get_point1() const;
	const Vec2i get_point2() const;
	const Vec2i get_point3() const;

	const static Vec3f calc_normal(Vec3f a, Vec3f b)
	{
		return Vec3f(
			a.y * b.z - a.z * b.y, 
			a.z * b.x - a.x * b.z, 
			a.x * b.y - a.y * b.x);
	}
};
