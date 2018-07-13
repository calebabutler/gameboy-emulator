
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "my_sdl.h"

int main()
{
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
	initiate_my_sdl(&sdl_window, &sdl_renderer, "Gameboy", 160, 144);

	bool window_is_open = true;
	SDL_Event sdl_event;
	while (window_is_open) {
		while (SDL_PollEvent(&sdl_event) != 0) {
			if (sdl_event.type == SDL_QUIT) {
				window_is_open = false;
			}
		}
	}

	destroy_my_sdl(&sdl_window, &sdl_renderer);
	return 0;
}

// vi: set ts=8 sts=8 noet sw=8 tw=80:
