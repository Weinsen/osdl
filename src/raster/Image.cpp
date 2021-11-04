#include "Image.h"

namespace OSDL {

Image::Image(std::string path) : path_(path) {}

Image::Image(std::string path, int w, int h) : path_(path) {
	geometry_.w = w;
	geometry_.h = h;
}

SDL_Surface* Image::Generate() {

	// TODO create resize method flag
	if (geometry_.w && geometry_.h) {

		SDL_Surface* isurface = IMG_Load(path_.data());
		if (!isurface) {
			printf("Error loading %s: %s\n", path_.data(), IMG_GetError());
			return NULL;
		}
		// SDL_SetColorKey(isurface, SDL_TRUE, SDL_MapRGB(isurface->format, 0, 0xFF, 0xFF));
		SDL_Surface* surface = CreateSurface(geometry_.w, geometry_.h);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0xff, 0xff, 0xff, 0x00));
		SDL_Rect r1, r2;

		if (false) {
			// Crop
			int w = std::min(isurface->w, geometry_.w);
			int h = std::min(isurface->h, geometry_.h);
			r1 = SDL_Rect{0, 0, w, h};
	        r2 = SDL_Rect{0, 0, w, h};
		} else if (false) {
			// Stretch
        	r1 = SDL_Rect{0, 0, geometry_.w, geometry_.h};
			r2 = SDL_Rect{0, 0, isurface->w, isurface->h};

		} else if (true) {
			// Vertical fit
			if (isurface->h < geometry_.h) {
	        	r1 = SDL_Rect{0, 0, geometry_.w, geometry_.h};
				r2 = SDL_Rect{(isurface->w-geometry_.w)/2, 0, geometry_.w, isurface->h};
			} else {
				int width = (long)(geometry_.h * isurface->h / isurface->w);
	        	r1 = SDL_Rect{(geometry_.w-width)/2, 0, width, geometry_.h};
				r2 = SDL_Rect{0, 0, isurface->w, isurface->h};
			}	

		}

        SDL_BlitScaled(isurface, &r2, surface, &r1);
        SDL_FreeSurface(isurface);
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);

		return surface;

	} else {

		SDL_Surface* surface = IMG_Load(path_.c_str());
		if (!surface) {
			printf("Error loading %s: %s\n", path_.data(), IMG_GetError());
			return NULL;
		}
		// SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

		return surface;

	}

}

}