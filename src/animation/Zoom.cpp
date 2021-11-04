#include "Zoom.h"

#include <cmath>

namespace OSDL {

Zoom::Zoom(uint32_t duration) : 
	Animation(duration), type_(ZoomAnimation::In) {}

Zoom::Zoom(uint32_t duration, ZoomAnimation type) : 
	Animation(duration), type_(type) {}

void Zoom::Animate() {

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
	int dt = now - start_;
	if (dt > duration_ms_) {
		dt = duration_ms_;
		is_done_ = true;
	}

	int height = 0;
	int width = 0;
	if (type_ == ZoomAnimation::In) {
		width = dt * origin_.w / duration_ms_;
		height = dt * origin_.h / duration_ms_;
	} else {
	// } else if (type_ == ZoomAnimation::Out) {
		width = dt * origin_.w / duration_ms_;
		height = dt * origin_.h / duration_ms_;
	}

	widget_->SetDimension(width, height);

}

}