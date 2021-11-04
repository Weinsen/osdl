#include "MainWindow.h"

//Screen dimension constants

namespace OSDL {

MainWindow::MainWindow() {
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 600, SDL_WINDOW_SHOWN );

	if(window == NULL) {
		throw MainWindowException(); 
    }

    #ifdef TARGET_IMX
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    #endif
}

MainWindow::~MainWindow() {
	SDL_DestroyWindow(window);
	window = NULL;
}

Renderer* MainWindow::CreateRenderer() {
	return new Renderer(window);
}

}