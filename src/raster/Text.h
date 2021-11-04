#ifndef SRC_RASTER_TEXT_H
#define SRC_RASTER_TEXT_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Raster.h"

namespace OSDL {

class Text : public Raster {

private:
	std::string text_;
	std::string fontname_;
	int fontsize_;
	const SDL_Color color_;
	SDL_Color outline_;
	int outline_width_;

public:
	Text(std::string text, int fontsize, std::string fontname, SDL_Color color);
	void SetOutline(int width, SDL_Color outline);
	SDL_Surface* Generate() override; 
	
};

}

#endif // SRC_RASTER_TEXT_H