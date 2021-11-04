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

std::thread* MainWindow::Loop() {

	return new std::thread([&](){

		bool quit = false;
		SDL_Event e;
		uint64_t frame;

		while (!quit) {
			uint64_t start = SDL_GetPerformanceCounter();
			frame++;
			while (SDL_PollEvent( &e ) != 0) {
	            if (e.type == SDL_QUIT) {
	                quit = true;
	            }
	        }

			for (auto& r : renderers_) {
				r->Render();
			}

			uint64_t end = SDL_GetPerformanceCounter();
			float elapsed = (end - start) * 1.0f / (float)SDL_GetPerformanceFrequency();
			float delay = 25.0f - elapsed * 1000.0f;
			if (delay > 0) {
				SDL_Delay(floor(delay));
			}

			end = SDL_GetPerformanceCounter();
			elapsed = (end - start) * 1.0f / (float)SDL_GetPerformanceFrequency();
			if (frame % 60 == 0) {
				// TODO remove
				printf("FPS: %3.1f\n", 1.0f/elapsed);
			}
		}
	});
}

Renderer* MainWindow::CreateRenderer() {
	Renderer* r = new Renderer(window);
	renderers_.push_back(r);
	return r;
}

}