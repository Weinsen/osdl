#ifndef SRC_WIDGET_GEOMETRY_H
#define SRC_WIDGET_GEOMETRY_H

#include <memory>

namespace OSDL {

class Geometry {

public:
	double x;
	double y;
	int w;
	int h;
	double angle;

	Geometry();
	Geometry(const Geometry &op);
	Geometry(double x, double y, double angle);
	Geometry(double x, double y, int w=0, int h=0, double angle=0.0);

	Geometry operator + (Geometry const &obj);
	Geometry &operator += (Geometry const &obj);
	Geometry operator - (Geometry const &obj);
	Geometry &operator -= (Geometry const &obj);
	Geometry &operator = (Geometry const &obj);

	int X();
	int Y();

};

}

#endif // SRC_WIDGET_GEOMETRY_H