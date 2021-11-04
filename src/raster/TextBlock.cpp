#include "TextBlock.h"

#include <iostream>
#include <list>
#include <sstream>

namespace OSDL {

TextBlock::TextBlock(std::string text, int fontsize, std::string fontname, SDL_Color fontcolor) : 
	text_(text), fontname_(fontname), fontsize_(fontsize), fontcolor_(fontcolor), alignment_(TextBlock::Default) {}

SDL_Surface* TextBlock::Generate() {

	geometry_.w = 0;
	geometry_.h = 0;
	if (parent_) {
		auto pos = parent_->GetPosition();
		if (pos->w > 0) {
			geometry_.w = pos->w;
		}
		if (pos->h > 0) {
			geometry_.h = pos->h;
		}
	}

    // TODO better treatment
    if (text_.empty()) {
        text_ = " ";
    }

    SDL_Surface* background = CreateSurface(geometry_.w, geometry_.h);

	TTF_Font* font = TTF_OpenFont(("./assets/fonts/" + fontname_).data(), fontsize_);
	int hspacer, vspacer;
	TTF_SizeText(font, " ", &hspacer, &vspacer);

	std::istringstream iss(text_);
    std::string word;
	int xpos = 0, ypos = 0;

    while(iss) {
    	int word_width = 0;
    	int line_width = 0;
    	std::list<std::string> line_words;

    	while (line_width < geometry_.w && iss) {
            if (!word.empty() || iss >> word) {
                TTF_SizeText(font, word.data(), &word_width, NULL);
            } else {
                break;
            }

    		if (word_width + line_width + hspacer >= geometry_.w) {
    			break;
    		} else {
    			line_width += hspacer + word_width;
    			line_words.push_back(word);
                word = "";
    		}
    	}

    	if (alignment_ & Alignment::Left) {
    		xpos = 0;
    	} else if (alignment_ & Alignment::HCenter) {
    		xpos = (geometry_.w - line_width)/2;
    	} else if (alignment_ & Alignment::Right) {
    		xpos = (geometry_.w - line_width);
    	} else if (alignment_ & Alignment::HJustify) {
    		// TODO justify text
    		xpos = 0;
    	}

    	for (auto const &w : line_words) {
			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, w.data(), fontcolor_);
    		SDL_Rect r1{0, 0, surface->w, surface->h};
	        SDL_Rect r2{xpos, ypos, surface->w, surface->h};
	        SDL_BlitSurface(surface, &r1, background, &r2);
	        xpos += hspacer + surface->w;
	    	SDL_FreeSurface(surface);
    	}

    	xpos = 0;
    	ypos += vspacer;
    }

    TTF_CloseFont(font);
	return background;
}

void TextBlock::SetAlignment(TextBlock::Alignment align) {
	alignment_ = align;
}


}