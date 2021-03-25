#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //SDL2找不到不管 编译才有\emsdk\upstream\emscripten\cache\wasm

#include "shared.h"

Uint32 currentTime, lastTime;
SDL_Event event;

AppContext context;


void GetData()
{
	EM_ASM_INT("getFFTData()"); //then js content call  GetArrayHEAPF32
}

//call by js
void EMSCRIPTEN_KEEPALIVE GetArrayHEAP(unsigned char *array, int length)
{
	PortData(array);
}

void Update(void)
{
	currentTime = SDL_GetTicks(); //milliseconds
	context.currentTime = currentTime;
	context.deltaTime = currentTime - lastTime;
	lastTime = currentTime;

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