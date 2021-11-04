#ifndef SRC_RASTER_ROUNDBOX_H
#define SRC_RASTER_ROUNDBOX_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Raster.h"

namespace OSDL {

class Roundbox : public Raster {

public:

	enum Corner {
		TOPLEFT     = 0x01,
		TOPRIGHT    = 0x02,
		TOP         = 0x03,
		BOTTOMRIGHT = 0x04,
		RIGHT       = 0x06,
		BOTTOMLEFT  = 0x08,
		LEFT        = 0x09,
		BOTTOM      = 0x0C,
		ALL         = 0x0F
	};
	
	Roundbox(int width, int height, int radius, SDL_Color color);
	Roundbox(int width, int height, int radius, Corner corner, SDL_Color color);
	SDL_Surface* Generate() override; 

private:
	const SDL_Color color_;
	int radius_;
	Corner corner_;
	
};

}

#endif // SRC_RASTER_ROUNDBOX_H