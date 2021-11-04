#ifndef SRC_ANIMATION_ANIMATION_H
#define SRC_ANIMATION_ANIMATION_H

#include "Widget.h"
#include "Geometry.h"

namespace OSDL {

class Geometry;
class Widget;

class Animation {

protected:
	bool is_done_;
	uint32_t duration_ms_;
	uint32_t start_;
	Geometry direction_;
	Geometry origin_;
	Widget* widget_;

public:
	Animation();
	Animation(uint32_t duration);
	Animation(Geometry& direction, uint32_t duration);
	void SetWidget(Widget* widget);
	bool IsDone();
	virtual void Animate() = 0;
};

}

#endif // SRC_ANIMATION_ANIMATION_H