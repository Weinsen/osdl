#ifndef SRC_ANIMATION_SLIDE_H
#define SRC_ANIMATION_SLIDE_H

#include "Animation.h"
#include "Geometry.h"

namespace OSDL {

class Slide : public Animation {

public:
	enum SlideAnimation {
		Linear,
		Elastic
	};
	Slide(Geometry& direction, uint32_t duration);
	Slide(Geometry& direction, uint32_t duration, SlideAnimation type);
	~Slide();
	void Animate() override;

private:
	SlideAnimation type_;

};

}

#endif // SRC_ANIMATION_SLIDE_H