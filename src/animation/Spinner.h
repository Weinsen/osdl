#ifndef SRC_ANIMATION_SPINNER_H
#define SRC_ANIMATION_SPINNER_H

#include "Animation.h"
#include "Geometry.h"

namespace OSDL {

class Spinner : public Animation {

public:
	Spinner(uint32_t duration, bool clockwise=true);
	void Animate() override;

private:
	bool clockwise_;

};

}

#endif // SRC_ANIMATION_SPINNER_H