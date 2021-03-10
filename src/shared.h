#include <SDL2/SDL.h>

#ifndef MY_SHARED_H
#define MY_SHARED_H

typedef struct Actor Actor;
typedef struct AppContext AppContext;

struct AppContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

int TestCube(Actor **);


#endif