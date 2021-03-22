#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#ifndef MY_SHARED_H
#define MY_SHARED_H

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600

#define FREQ_COUNT 16

typedef struct Actor Actor;
typedef struct AppContext AppContext;

struct AppContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 deltaTime,currentTime;
};
int Init(AppContext *);
int Render(AppContext *);
void GenarateCubes(uint count, GLfloat **pVertex, uint *vertexCount, GLshort **pIndices, uint *indicesCount);
#endif