#include "Animation.h"

namespace OSDL {

Animation::Animation() : is_done_(false), start_(0) {}

Animation::Animation(uint32_t duration) : 
	duration_ms_(duration), is_done_(false), start_(0) {}

Animation::Animation(Geometry& direction, uint32_t duration) : 
	duration_ms_(duration), direction_(direction), is_done_(false), start_(0) {}

bool Animation::IsDone() {
	return is_done_;
}

void Animation::SetWidget(Widget* widget) {
	if (widget_) {
		widget_->SetAnimation(NULL);
	}
	widget_ = widget;
}


}