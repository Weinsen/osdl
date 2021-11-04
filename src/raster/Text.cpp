#include "Text.h"

namespace OSDL {

Text::Text(std::string text, int fontsize, std::string fontname, SDL_Color color) : 
	text_(text), fontname_(fontname), fontsize_(fontsize), color_(color), outline_width_(0), outline_(color) {}

void Text::SetOutline(int width, SDL_Color outline) {
	outline_ = outline;
	outline_width_ = width;
}

SDL_Surface* Text::Generate() {

	// TODO better treatment
	if (text_.empty()) {
		text_ = " ";
	}

	TTF_Font* font_ = TTF_OpenFont(("./assets/fonts/" + fontname_).data(), fontsize_);
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font_, text_.data(), color_);

	if (outline_width_ <= 0) {

		geometry_.w = surface->w;
	    geometry_.h = surface->h;
	    TTF_CloseFont(font_);
		return surface;

	}

	TTF_SetFontOutline(font_, outline_width_);
	SDL_Surface* outline_s = TTF_RenderUTF8_Blended(font_, text_.data(), outline_);
	SDL_Rect rect = {outline_width_, outline_width_, outline_s->w, outline_s->h};

	SDL_SetSurfaceBlendMode(outline_s, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(surface, NULL, outline_s, &rect); 
	SDL_FreeSurface(surface); 

    TTF_CloseFont(font_);
	return outline_s;

    
}

}