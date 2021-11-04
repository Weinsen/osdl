#ifndef SRC_RASTER_TEXTBLOCK_H
#define SRC_RASTER_TEXTBLOCK_H

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Raster.h"

namespace OSDL {

class TextBlock : public Raster {

public:

	enum Alignment {
		Default    = 0x0000,
		Left 	   = 0x0001,
		HCenter	   = 0x0002,
		Right 	   = 0x0004,
		HJustify   = 0x0008,
		HAlignment = 0x000F,
		Center 	   = 0x0022,
		Justify	   = 0x0088,
	};

	TextBlock(std::string text, int fontsize, std::string fontname, SDL_Color fontcolor);
	SDL_Surface* Generate() override; 

	void SetAlignment(Alignment align);

private:
	std::string text_;
	std::string fontname_;
	int fontsize_;
	Alignment alignment_;
	const SDL_Color fontcolor_;
	
};

}

#endif // SRC_RASTER_TEXTBLOCK_H