#include "Roundbox.h"

namespace OSDL {

Roundbox::Roundbox(int width, int height, int radius, SDL_Color color) : 
	color_(color), radius_(radius), corner_(Corner::ALL) {

	geometry_.w = width;
	geometry_.h = height;
	
}

Roundbox::Roundbox(int width, int height, int radius, Corner corner, SDL_Color color) : 
	color_(color), radius_(radius), corner_(corner) {

	geometry_.w = width;
	geometry_.h = height;
	
}

SDL_Surface* Roundbox::Generate() {

	uint8_t radmap[radius_][radius_] = {0};

	SDL_Surface* psurface = CreateSurface(geometry_.w, geometry_.h);

	// SDL_Surface* psurface = SDL_CreateRGBSurface(0, geometry_.w, geometry_.h, 32, 0, 0, 0, 0);
	SDL_FillRect(psurface, NULL, SDL_MapRGBA(psurface->format, color_.r, color_.g, color_.b, color_.a));
	SDL_Surface* surface = SDL_ConvertSurfaceFormat(psurface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(psurface); 

	uint8_t bpp = surface->format->BytesPerPixel;
	int x, y = 0;
	// int i, j = 0;
	auto transparent = SDL_MapRGBA(surface->format, 0xFF, 0xFF, 0xFF, 0x00);

	for (x=0; x<radius_; x++) {
		for (y=0; y<radius_; y++) {
			if (x*x + y*y <= radius_*radius_) {
				radmap[radius_-x-1][radius_-y-1] = 0xff;
			} else {
				radmap[radius_-x-1][radius_-y-1] = 0x00;
			}
		}
	}

	bool tl = (corner_ & 0x01) != 0;
	bool tr = (corner_ & 0x02) != 0;
	bool br = (corner_ & 0x04) != 0;
	bool bl = (corner_ & 0x08) != 0;

	for (y=0; y<radius_; y++) {
		for (x=0; x<radius_; x++) {
			if (!radmap[x][y]) {
				if (tl) { // TOP LEFT
					auto pixel_ptr = surface->pixels + y * surface->pitch + x * bpp;
					*(uint32_t *) pixel_ptr = transparent;
				}
				if (tr) { // TOP RIGHT
					auto pixel_ptr = surface->pixels + y * surface->pitch + (geometry_.w-x-1) * bpp;
					*(uint32_t *) pixel_ptr = transparent;
				}
				if (bl) { // BOT LEFT
					auto pixel_ptr = surface->pixels + (geometry_.h-y-1) * surface->pitch + x * bpp;
					*(uint32_t *) pixel_ptr = transparent;
				}
				if (br) { // BOT RIGHT
					auto pixel_ptr = surface->pixels + (geometry_.h-y-1) * surface->pitch + (geometry_.w-x-1) * bpp;
					*(uint32_t *) pixel_ptr = transparent;
				}
				
			}
		}
	}

	return surface;
}

}