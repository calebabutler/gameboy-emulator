
#ifndef _GAMEBOY_MY_SDL_H
#define _GAMEBOY_MY_SDL_H

// my_sdl is a series of functions for starting and destroying SDL. It
// moves more code out of the main loop and puts all of the SDL stuff in
// one place. It is called my_sdl so it doesn't get confused with the
// actual SDL library.

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

void my_sdl_error_handler(const int return_value,
	const char *const function_name);
void initiate_my_sdl(
	SDL_Window **my_sdl_window,
	SDL_Renderer **my_sdl_renderer,
	const char *my_sdl_window_title,
	const unsigned int my_sdl_window_width,
	const unsigned int my_sdl_window_height);
void destroy_my_sdl(SDL_Window **my_sdl_window,
	SDL_Renderer **my_sdl_renderer);


#endif // _GAMEBOY_MY_SDL_H

// vi: set ts=8 sts=8 noet sw=8 tw=80:
