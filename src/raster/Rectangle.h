#ifndef SRC_RASTER_RECTANGLE_H
#define SRC_RASTER_RECTANGLE_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Raster.h"

namespace OSDL {

class Rectangle : public Raster {

private:
	const SDL_Color color_;

public:
	Rectangle(int width, int height, SDL_Color color);
	SDL_Surface* Generate() override; 
	
};

}

#endif // SRC_RASTER_RECTANGLE_H