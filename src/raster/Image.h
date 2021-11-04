#ifndef SRC_RASTER_IMAGE_H
#define SRC_RASTER_IMAGE_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Raster.h"

namespace OSDL {

class Image : public Raster {

private:
	std::string path_;

public:
	Image(std::string path);
	Image(std::string path, int w, int h);
	SDL_Surface* Generate() override; 
	
};

}

#endif // SRC_RASTER_IMAGE_H