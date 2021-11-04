#include "Geometry.h"

namespace OSDL {

Geometry::Geometry() :
	x(0), y(0), w(0), h(0), angle(0.0) {}

Geometry::Geometry(const Geometry &op) :
	x(op.x), y(op.y), w(op.w), h(op.h), angle(op.angle) {}

Geometry::Geometry(double x, double y, int w, int h, double angle) :
	x(x), y(y), w(w), h(h), angle(angle) {}

Geometry::Geometry(double x, double y, double angle) : 
	x(x), y(y), angle(angle) {}

Geometry Geometry::operator + (Geometry const &op) {
	Geometry ret;
	ret.x = x + op.x;
	ret.y = y + op.y;
	ret.angle = angle + op.angle;
	return ret;
}

Geometry &Geometry::operator += (Geometry const &op) {
	x += op.x;
	y += op.y;
	angle += op.angle;
	return *this;
}

Geometry Geometry::operator - (Geometry const &op) {
	Geometry ret;
	ret.x = x - op.x;
	ret.y = y - op.y;
	ret.angle = angle - op.angle;
	return ret;
}

Geometry &Geometry::operator -= (Geometry const &op) {
	x -= op.x;
	y -= op.y;
	angle -= op.angle;
	return *this;
}

Geometry &Geometry::operator = (Geometry const &op) {
	x = op.x;
	y = op.y;
	h = op.h;
	w = op.w;
	angle = op.angle;
	return *this;
}

int Geometry::X() {
	return x;
}

int Geometry::Y() {
	return y;
}

}