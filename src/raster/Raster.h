#ifndef SRC_RASTER_H
#define SRC_RASTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include "Geometry.h"

namespace OSDL {

class Raster {

protected:
	Geometry geometry_;
	std::list<Raster*> childs_;
	Raster* parent_;
	bool mirror_;
	SDL_BlendMode blendMode_;
	SDL_Surface* CreateSurface(int w, int h);

public:
	Raster();
	~Raster();
	void Move(const Geometry& pos);
	void Move(int x, int y);
	void SetPosition(const Geometry& pos);
	void SetParent(Raster* parent_);
	void AddChild(Raster* child);
	void AddChild(Raster* child, Geometry& position);
	void SetMirror(bool mirror);
	void SetBlendMode(SDL_BlendMode blendMode);
	SDL_Surface* Render(const Geometry* position = NULL);
	Geometry *GetPosition();
	virtual SDL_Surface* Generate() = 0;
};

}

#endif // SRC_RASTER_H