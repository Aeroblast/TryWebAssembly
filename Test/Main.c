#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //SDL2找不到不管 编译才有\emsdk\upstream\emscripten\cache\wasm

#include "shared.h"
#include "Actor.h"

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600
#define FLOAT32_BYTE_SIZE 4
#define STRIDE FLOAT32_BYTE_SIZE * 4
#define ACTOR_COUNT 2
Uint32 currentTime, lastTime;
SDL_Event event;

AppContext context;

Actor *actors[ACTOR_COUNT];

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
	glClearColor(0, 0, 0.3f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < ACTOR_COUNT; i++)
	{
		actors[i]->Update(actors[i], &context);
	}

}


int Start(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	context.window = SDL_CreateWindow(0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, (SDL_WINDOW_OPENGL));
	context.renderer = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(context.renderer, 64, 64, 64, 255);
	SDL_RenderClear(context.renderer);
	CompileShader();
	TestCube(&actors[0]);
	TestCube2(&actors[1]);
	for (int i = 0; i < ACTOR_COUNT; i++)
	{
		actors[i]->Init(actors[i], &context);
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
	printf("Start() End\n");
	return 0;
}
int main()
{
	emscripten_set_main_loop(Update, 0, 0);
	Start();
}