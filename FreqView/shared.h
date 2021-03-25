#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#ifndef MY_SHARED_H
#define MY_SHARED_H

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600

#define FREQ_COUNT 128

typedef struct AppContext AppContext;

struct AppContext
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 deltaTime,currentTime;
};

//render ==> GetData ==>getFFTData (JavaScript) => PortData

//Main.c
void GetData();


//render.c
void PortData(unsigned char* heightData);
int Init(AppContext *);
int Render(AppContext *);

//gen_vertex.c
void GenarateCubes(unsigned int count, GLfloat **pVertex, unsigned int *vertexCount, GLshort **pIndices, unsigned int  *indicesCount);
#endif