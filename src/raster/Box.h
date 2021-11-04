#ifndef SRC_RASTER_Box_H
#define SRC_RASTER_Box_H

#include <SDL2/SDL_ttf.h>

#include "Raster.h"

namespace OSDL {

class Box : public Raster {

public:

	enum Alignment {
		Default    = 0x0000,
		Left 	   = 0x0001,
		HCenter	   = 0x0002,
		Right 	   = 0x0004,
		HJustify   = 0x0008,
		HAlignment = 0x000F,
		Top 	   = 0x0010,
		VCenter	   = 0x0020,
		Bottom 	   = 0x0040,
		VJustify   = 0x0080,
		VAlignment = 0x00F0,
		Center 	   = 0x0022,
		Justify	   = 0x0088,
	};
	
	Box(uint width=0, uint height=0);
	Box(SDL_Color color, uint width=0, uint height=0);
	SDL_Surface* Generate() override;

	void SetHSpace(uint space);
	void SetAlignment(Alignment align);


private:
	const SDL_Color color_;
	int vspace_;
	int hspace_;
	Alignment alignment_;
	
};

Box::Alignment operator | (Box::Alignment a, Box::Alignment b);
Box::Alignment& operator |=(Box::Alignment& a, Box::Alignment b);
Box::Alignment operator &(Box::Alignment a, Box::Alignment b);
Box::Alignment& operator &=(Box::Alignment& a, Box::Alignment b);

}


#endif // SRC_RASTER_Box_H