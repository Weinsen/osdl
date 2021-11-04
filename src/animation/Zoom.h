#ifndef SRC_ANIMATION_ZOOM_H
#define SRC_ANIMATION_ZOOM_H

#include "Animation.h"
#include "Geometry.h"

namespace OSDL {

class Zoom : public Animation {

public:
	enum ZoomAnimation {
		In,
		Out
	};
	Zoom(uint32_t duration);
	Zoom(uint32_t duration, ZoomAnimation type);
	void Animate() override;

private:
	ZoomAnimation type_;

};

}

#endif // SRC_ANIMATION_ZOOM_H