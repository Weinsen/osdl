#include "Slide.h"

#include <cmath>

namespace OSDL {

Slide::Slide(Geometry& direction, uint32_t duration) : 
	Animation(direction, duration), type_(SlideAnimation::Linear) {}

Slide::Slide(Geometry& direction, uint32_t duration, SlideAnimation type) : 
	Animation(direction, duration), type_(type) {}

void Slide::Animate() {

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
	double dx, dy, dtheta;
	int dt = now - start_;
	if (dt > duration_ms_) {
		dt = duration_ms_;
		is_done_ = true;
	}

	if (type_ == SlideAnimation::Elastic) {
		// (1-cos(x*pi))/2
		double dur = (3.14159265 * dt / duration_ms_);
		// dx = dt * direction_.x / duration_ms_ + origin_.x;
		// dy = dt * direction_.y / duration_ms_ + origin_.y;
		// dtheta = dt * direction_.angle / duration_ms_ + origin_.angle;
		dx = direction_.x * (1-cos(dur))/2 + origin_.x;
		dy = direction_.y * (1-cos(dur))/2 + origin_.y;
		dtheta = direction_.angle * (1-cos(dur))/2 + origin_.angle;
	} else {
		dx = dt * direction_.x / duration_ms_ + origin_.x;
		dy = dt * direction_.y / duration_ms_ + origin_.y;
		dtheta = dt * direction_.angle / duration_ms_ + + origin_.angle;
	}

	widget_->SetPosition(Geometry{dx, dy, dtheta});

}

}