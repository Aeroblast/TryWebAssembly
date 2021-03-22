#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //SDL2找不到不管 编译才有\emsdk\upstream\emscripten\cache\wasm

#include "shared.h"

Uint32 currentTime, lastTime;
SDL_Event event;

AppContext context;

void Update(void)
{
	/*
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{

			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:

				break;
			}
		}
	}

	currentTime = SDL_GetTicks();
	Uint32 deltaTime = currentTime - lastTime;
	lastTime = currentTime;
*/
	Render(&context);
}

int Start(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	context.window = SDL_CreateWindow(0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, (SDL_WINDOW_OPENGL));
	context.renderer = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(context.renderer, 64, 64, 64, 255);
	SDL_RenderClear(context.renderer);
	Init(&context);
	return 0;
}
int main()
{
	emscripten_set_main_loop(Update, 0, 0);
	Start();
}