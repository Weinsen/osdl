#ifndef SRC_RASTER_CIRCLE_H
#define SRC_RASTER_CIRCLE_H

#include <SDL2/SDL_ttf.h>

#include "Raster.h"

namespace OSDL {

class Circle : public Raster {

public:
	
	Circle(int radius, SDL_Color color);
	SDL_Surface* Generate() override; 

private:
	const SDL_Color color_;
	int radius_;
	
};

}

#endif // SRC_RASTER_CIRCLE_H