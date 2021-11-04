#include "Rectangle.h"

namespace OSDL {

Rectangle::Rectangle(int width, int height, SDL_Color color) : color_(color) {

	geometry_.w = width;
	geometry_.h = height;
	
}

SDL_Surface* Rectangle::Generate() {

	SDL_Surface* psurface = CreateSurface(geometry_.w, geometry_.h);

	SDL_FillRect(psurface, NULL, SDL_MapRGBA(psurface->format, color_.r, color_.g, color_.b, color_.a));
	SDL_Surface* surface = SDL_ConvertSurfaceFormat(psurface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(psurface); 

	return surface;
}

}