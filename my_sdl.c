
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "my_sdl.h"

// note: This should only be used for SDL functions that are not critical,
// e.g., SDL_SetRenderDrawColor or SDL_RenderClear. Critical functions, like
// SDL_CreateWindow, can use this function as long as it is with other
// functions like SDL_Quit.
void my_sdl_error_handler(const int return_value,
	const char *const function_name)
{
	if (return_value < 0) {
		fprintf(stderr, "%s failed.\n", function_name);
		fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
	}
}

void initiate_my_sdl(
	SDL_Window **my_sdl_window,
	SDL_Renderer **my_sdl_renderer,
	const char *my_sdl_window_title,
	const unsigned int my_sdl_window_width,
	const unsigned int my_sdl_window_height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		my_sdl_error_handler(-1, "SDL_Init()");
		exit(1);
	}

	(*my_sdl_window) = SDL_CreateWindow(
		my_sdl_window_title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		my_sdl_window_width,
		my_sdl_window_height,
		SDL_WINDOW_SHOWN);
	if ((*my_sdl_window) == NULL) {
		my_sdl_error_handler(-1, "SDL_CreateWindow()");
		SDL_Quit();
		exit(2);
	}
	(*my_sdl_renderer) = SDL_CreateRenderer((*my_sdl_window), -1,
		SDL_RENDERER_ACCELERATED);
	if ((*my_sdl_renderer) == NULL) {
		my_sdl_error_handler(-1, "SDL_CreateRenderer()");
		SDL_DestroyWindow((*my_sdl_window));
		(*my_sdl_window) = NULL;
		my_sdl_window = NULL;
		SDL_Quit();
		exit(3);
	}

	// set white background
	my_sdl_error_handler(
		SDL_SetRenderDrawColor((*my_sdl_renderer), 255, 255, 255, 255),
		"SDL_SetRenderDrawColor()");
	my_sdl_error_handler(SDL_RenderClear((*my_sdl_renderer)),
		"SDL_RenderClear()");
	SDL_RenderPresent((*my_sdl_renderer));
}

void destroy_my_sdl(SDL_Window **my_sdl_window, SDL_Renderer **my_sdl_renderer)
{
	SDL_DestroyRenderer((*my_sdl_renderer));
	(*my_sdl_renderer) = NULL;
	my_sdl_renderer = NULL;
	SDL_DestroyWindow((*my_sdl_window));
	(*my_sdl_window) = NULL;
	my_sdl_window = NULL;
	SDL_Quit();
}

// vi: set ts=8 sts=8 noet sw=8 tw=80:
