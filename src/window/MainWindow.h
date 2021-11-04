#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <exception>

#include "Renderer.h"

namespace OSDL {

class MainWindowException : public std::exception {
	const char * what () const throw () {
		return "Failure";
	}
};

class MainWindow {
private:
	SDL_Window* window;

public:
	MainWindow();
	~MainWindow();
	Renderer* CreateRenderer();
};

} // namespace MainWindow

#endif // MAIN_WINDOW_H
