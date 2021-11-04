#include "MainWindow.h"

//Screen dimension constants

namespace OSDL {

MainWindow::MainWindow() {
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 600, SDL_WINDOW_SHOWN );

	if(window == NULL) {
		throw MainWindowException(); 
    }
}

MainWindow::~MainWindow() {
	SDL_DestroyWindow(window);
	window = NULL;
}

void MainWindow::SetFullscreen() {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}


Renderer* MainWindow::CreateRenderer() {
	return new Renderer(window);
}

}