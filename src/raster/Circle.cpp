#include "Circle.h"

namespace OSDL {

Circle::Circle(int radius, SDL_Color color) : 
	color_(color), radius_(radius) {

	if (radius % 2) {
		geometry_.w = radius_ * 2 + 1;
		geometry_.h = radius_ * 2 + 1;
	} else {
		geometry_.w = radius_ * 2;
		geometry_.h = radius_ * 2;
	}
	
}

// TODO cache raster
// TODO configurable blur
SDL_Surface* Circle::Generate() {

	uint8_t radmap[geometry_.w][geometry_.h] = {0};

	SDL_Surface* surface = CreateSurface(geometry_.w, geometry_.h);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color_.r, color_.g, color_.b, color_.a));

	uint8_t bpp = surface->format->BytesPerPixel;
	int x, y = 0;
	auto transparent = SDL_MapRGBA(surface->format, 0xFF, 0xFF, 0xFF, 0x00);

	for (x=-radius_; x<radius_; x++) {
		for (y=-radius_; y<radius_; y++) {
			double X = x;
			double Y = y;
			if (radius_%2 == 0) {
				X+=0.5;
				Y+=0.5;
			}
			double r2 = sqrt(X*X + Y*Y);
			if (r2 > radius_-1 && r2 < radius_+1) {
				radmap[x+radius_][y+radius_] = (long)(127 * ((radius_-1)-r2));
			} else if (r2 <= radius_) {
				radmap[x+radius_][y+radius_] = 0xff;
			} else {
				radmap[x+radius_][y+radius_] = 0x00;
			}
		}
	}

	for (x=0; x<geometry_.w; x++) {
		for (y=0; y<geometry_.h; y++) {
			if (radmap[x][y] != 0xff) {
				auto pixel_ptr = surface->pixels + y * surface->pitch + x * bpp;
				// *(uint32_t *) pixel_ptr = transparent;
				*(uint32_t *) pixel_ptr = SDL_MapRGBA(surface->format, color_.r, color_.g, color_.b, radmap[x][y]);
			}
		}
	}

	return surface;
}

}