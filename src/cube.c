#include <GLES2/gl2.h>
#include "shared.h"
#include "Actor.h"
#include "matrix.h"
//#include "data.h"

float angle = 0;
int Cube_Update(Actor *self, AppContext *context)
{
    angle += 1;
    if (angle > 360)
    {
        angle -= 360;
    }
    Matrix_IdentityFunction(self->modelViewMatrix);
    Matrix_RotateX(self->modelViewMatrix, angle);
    Matrix_RotateY(self->modelViewMatrix, angle);
    Matrix_Translate(self->modelViewMatrix, 0.0f, 0.0f, -10.0f);
    Actor_Render(self, context);
    return 0;
}
char img0[] = "data/Test0.png";
char img1[] = "data/Test1.png";
int TestCube(Actor **ppcube)
{
    Actor *pcube = malloc(sizeof(Actor));
    *ppcube = pcube;
    //pcube->p_vertex_shader_code = &vertex_shader_code;
    //pcube->p_fragment_shader_code = &fragment_shader_code;
    pcube->Init = Actor_Init;
    pcube->Update = Cube_Update;
    pcube->textureFilename = img0;
    return 0;
}