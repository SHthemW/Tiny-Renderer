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
	bool inside(Vec2i point);
	Vec2i get_point1();
	Vec2i get_point2();
	Vec2i get_point3();
};
