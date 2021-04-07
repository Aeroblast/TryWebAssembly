#include "shared.h"
GLfloat cubeVertex[] = {
    0.0f, 1.0f, 0.0f, //0
    1.0f, 1.0f, 0.0f, //1
    1.0f, 1.0f, 1.0f, //2
    0.0f, 1.0f, 1.0f, //3
    0.0f, 0.0f, 0.0f, //4
    1.0f, 0.0f, 0.0f, //5
    1.0f, 0.0f, 1.0f, //6
    0.0f, 0.0f, 1.0f, //7
};
GLushort cubeIndices[] = {
    0, 1, 2, 2, 3, 0, //top
    4, 5, 6, 6, 7, 4, //buttom
    4, 5, 1, 1, 0, 4, //front
    7, 6, 2, 2, 3, 7, //back
    4, 0, 3, 3, 7, 4, //left
    5, 1, 2, 2, 6, 5  //right
};
#define CUBE_V_COUNT (sizeof(cubeVertex) / sizeof(GLfloat))  //24
#define CUBE_I_COUNT (sizeof(cubeIndices) / sizeof(GLshort)) //36

//#define OLD_GEN_METHOD

void GenarateCubes(uint count, GLfloat **pVertex, uint *vertexCount, GLshort **pIndices, uint *indicesCount)
{
    GLfloat *vertex = malloc(count * sizeof(cubeVertex));
    GLshort *indices = malloc(count * sizeof(cubeIndices));
    *vertexCount = CUBE_V_COUNT * count;
    *indicesCount = CUBE_I_COUNT * count;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < CUBE_V_COUNT; j++)
        {
            GLfloat t = cubeVertex[j] / count;
            switch (j % 3)
            {
            case 0: //x
                t = t + i * (1.0f / count);
                t -= 0.5f;
                break;
            case 1: //y
                t = cubeVertex[j];
                break;
            case 2: //z
                t -= 0.5f / count;
                break;
            }
            if (j < CUBE_V_COUNT / 2)
            {
                //Gen Top
                vertex[j + CUBE_V_COUNT / 2 * i] = t;
            }
            else
            {
                //buttom
                vertex[j + CUBE_V_COUNT / 2 * i + CUBE_V_COUNT / 2 * (count - 1)] = t;
            }
        }
        for (int j = 0; j < CUBE_I_COUNT; j++)
        {
            GLushort t = cubeIndices[j];
            if (t >= CUBE_V_COUNT / 3 / 2)
            {
                t += CUBE_V_COUNT / 3 / 2 * (count - 1);
            }
            indices[i * CUBE_I_COUNT + j] = t + CUBE_V_COUNT / 3 / 2 * i;
        }
    }
    *pVertex = vertex;
    *pIndices = indices;
}