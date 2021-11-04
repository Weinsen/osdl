#include "Renderer.h"

namespace OSDL {

Renderer::Renderer(SDL_Window* window) {
	renderer_ = SDL_CreateRenderer(window, -1, 0);
	if (!renderer_) {
        throw "No renderer created";
	}
	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer_);
    renderer_ = NULL;
}

// TODO check return 
void Renderer::Clear() {
    SDL_RenderClear(renderer_);
}

// TODO check return 
void Renderer::RenderPresent() {
    SDL_RenderPresent(renderer_);
}

// TODO check return 
void Renderer::RenderWidgets() {
	for (auto w : widgets_) {
		w->Render();
	}
}

// TODO check return 
void Renderer::Render() {
	std::lock_guard<std::mutex> lock(mtx_);
	Clear();
	RenderWidgets();
	RenderPresent();
	update_ = false;
}

void Renderer::AddWidget(Widget* widget) {
	std::lock_guard<std::mutex> lock(mtx_);
	widgets_.push_back(widget);
	widget->SetRenderer(renderer_);
}

void Renderer::RemoveWidget(Widget* widget) {
	std::lock_guard<std::mutex> lock(mtx_);
	widgets_.remove(widget);
}

}