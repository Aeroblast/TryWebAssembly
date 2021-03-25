#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#ifndef MY_SHARED_H
#define MY_SHARED_H

typedef struct Actor Actor;
typedef struct AppContext AppContext;

struct AppContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};
int CompileShader();
int TestCube(Actor **);
int TestCube2(Actor **ppcube);

#endif