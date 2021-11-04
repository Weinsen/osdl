#include "Box.h"

#include <list>

namespace OSDL {

Box::Box(uint width, uint height) : hspace_(0), vspace_(0), color_(SDL_Color{0, 0, 0, 0}) {
    alignment_ = Alignment::Default;
	geometry_.w = width;
	geometry_.h = height;
}

Box::Box(SDL_Color color, uint width, uint height) : color_(color), hspace_(0), vspace_(0) {
    alignment_ = Alignment::Default;
	geometry_.w = width;
	geometry_.h = height;
}

SDL_Surface* Box::Generate() {

    Geometry pos = geometry_;
    // SDL_Rect r1{pos.x(), pos.y(), geometry_.w, geometry_.h};

    std::list<SDL_Surface*> surfaces;

    // Render
    for (auto c : childs_) {
        SDL_Surface* c_s = c->Render(&pos);
        surfaces.push_back(c_s);
    }

    // Select
    SDL_Surface* last = NULL;
    int final_width = 0;
    int max_height = 0;
	int h = geometry_.h;
	int w = geometry_.w;
    int xpos = 0, ypos = 0;
    for (auto c_s : surfaces) {
        if (!c_s) continue;
    	if (c_s->w <= w-xpos || !w) {
        	last = c_s;
    		xpos += hspace_ + c_s->w;

        	final_width += hspace_ + c_s->w;
        	if (c_s->h > max_height) max_height = c_s->h;
    	}
    }

    if (!geometry_.w) geometry_.w = final_width;
    if (!geometry_.h) {
        geometry_.h = max_height;
    } else {
        max_height = geometry_.h;
    }
    h = geometry_.h;
	w = geometry_.w;

    SDL_Surface* psurface = CreateSurface(geometry_.w, geometry_.h);

	SDL_FillRect(psurface, NULL, SDL_MapRGBA(psurface->format, color_.r, color_.g, color_.b, color_.a));
	SDL_Surface* surface = SDL_ConvertSurfaceFormat(psurface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(psurface); 

    int xcor;
	if (alignment_ & Alignment::Right) {
		xcor = w - final_width;
	} else if (alignment_ & Alignment::HCenter) {
		xcor = (w - final_width) / 2;
	} else {
		xcor = 0;
	}

    // Blit
    xpos = 0;
    ypos = 0;
    for (auto c_s : surfaces) {
        if (!c_s) continue;
    	if (c_s->w <= w-xpos) {

    		int ycor;
    		if (alignment_ & Alignment::Bottom) {
    			ycor = max_height - c_s->h;
    		} else if (alignment_ & Alignment::VCenter) {
    			ycor = (max_height - c_s->h) / 2;
    		} else {
    			ycor = 0;
    		}

	    	SDL_Rect r1, r2;
	        r1 = SDL_Rect{xpos+xcor, ypos+ycor, c_s->w, c_s->h};
	        r2 = SDL_Rect{0, 0, c_s->w, c_s->h};
	    	SDL_BlitSurface(c_s, &r2, surface, &r1);

    		xpos += hspace_ + c_s->w;
	    	if (last == c_s) {
	    		break;
	    	}
	    }
    }

    // Clean up
    for (auto c_s : surfaces) {
        SDL_FreeSurface(c_s);
    }

    childs_.clear();

    return surface;

}

void Box::SetHSpace(uint space) {
	hspace_ = space;
}

void Box::SetAlignment(Alignment align) {
	alignment_ = align;
}


Box::Alignment operator |(Box::Alignment a, Box::Alignment b)
{
    return static_cast<Box::Alignment>(static_cast<int>(a) | static_cast<int>(b));
}

Box::Alignment operator &(Box::Alignment a, Box::Alignment b)
{
    return static_cast<Box::Alignment>(static_cast<int>(a) & static_cast<int>(b));
}

Box::Alignment& operator |=(Box::Alignment& a, Box::Alignment b)
{
    return a= a | b;
}

Box::Alignment& operator &=(Box::Alignment& a, Box::Alignment b)
{
    return a= a | b;
}

}