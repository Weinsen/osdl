#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <mutex>

#include "Widget.h"

namespace OSDL {

class Renderer {
private:
	SDL_Renderer* renderer_;
	std::list<Widget*> widgets_;
	std::mutex mtx_;
	bool update_;

public:
	Renderer(SDL_Window* window);
	~Renderer();
	void Clear();
	void Render();
	void RenderPresent();
	void RenderWidgets();
	void AddWidget(Widget* widget);
	void RemoveWidget(Widget* widget);
};

}

#endif