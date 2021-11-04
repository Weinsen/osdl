#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <exception>
#include <list>
#include <thread>

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
	std::list<Renderer*> renderers_;

public:
	MainWindow();
	~MainWindow();
	void SetFullscreen();
	Renderer* CreateRenderer();
	std::thread* Loop();
};

}

#endif // MAIN_WINDOW_H
