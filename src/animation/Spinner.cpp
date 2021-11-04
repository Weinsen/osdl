#include "Spinner.h"

#include <cmath>

namespace OSDL {

Spinner::Spinner(uint32_t duration, bool clockwise) : clockwise_(clockwise) {
	duration_ms_ = duration;
}

void Spinner::Animate() {

	if (!widget_) {
		return;
	}

	if (is_done_) {
		return;
	}

	if (!start_) {
		start_ = SDL_GetTicks();
		origin_ = *(widget_->GetPosition());
	}

	uint32_t now = SDL_GetTicks();

	int dt = (now - start_) % duration_ms_;

	double dtheta = cos((3.14159265 * dt) / (duration_ms_ * 2));
	dtheta = dtheta * dtheta;
	if (!clockwise_) dtheta *= -1;

	widget_->SetPosition(Geometry{origin_.x, origin_.y, 360*dtheta});

}

}