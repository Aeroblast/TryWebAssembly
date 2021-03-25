#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "matrix.h"
#include "shared.h"
#include "shader_strings.h"
//App
float projectionMatrix[16];
float modelViewMatrix[16];

GLfloat *vertexData;
uint vertexCount;
GLshort *indicesData;
uint indicesCount;

//GLfloat heightData[FREQ_COUNT] = {0.1f, 0.5f, 0.7f, 0.9f, 0.5f, 0.8f, 0.3f, 0.8f, 0.1f, 0.5f, 0.7f, 0.9f, 0.5f, 0.8f, 0.3f, 0.8f};
GLfloat heightDataForGPU[FREQ_COUNT * 4] = {0}; //only top face, 4 vertice per cube
void PortData(unsigned char *heightData)
{
    for (int i = 0; i < FREQ_COUNT; i++)
    {
        GLfloat t = heightData[i] / 256.0f;
        heightDataForGPU[i * 4] = t;
        heightDataForGPU[i * 4 + 1] = t;
        heightDataForGPU[i * 4 + 2] = t;
        heightDataForGPU[i * 4 + 3] = t;
    }
    glBufferSubData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), sizeof(heightDataForGPU), heightDataForGPU);
}
//GL
GLuint vertex_buffers[2];

GLuint program;

GLint a_position_location;
GLint a_height_location;
GLint u_modelView_location;
GLint u_projection_location;

int CompileShader()
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_code, 0);
    glCompileShader(vertex_shader);
    GLint compile_success = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_success);
    if (compile_success == GL_FALSE)
    {
        printf("failed to compile vertex shader\n");
        glDeleteShader(vertex_shader);
        return 0;
    }
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_code, 0);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_success);
    if (compile_success == GL_FALSE)
    {
        printf("failed to compile fragment shader\n");
        glDeleteShader(fragment_shader);
        return 0;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    GLint link_success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &link_success);
    if (link_success == GL_FALSE)
    {
        printf("failed to link program\n");
        glDeleteProgram(program);
        return 0;
    }

    return 0;
}
int Init(AppContext *context)
{

    GenarateCubes(FREQ_COUNT, &vertexData, &vertexCount, &indicesData, &indicesCount);
    CompileShader();
    glUseProgram(program);
    u_modelView_location = glGetUniformLocation(program, "u_modelView");
    u_projection_location = glGetUniformLocation(program, "u_projection");
    a_position_location = glGetAttribLocation(program, "a_position");
    a_height_location = glGetAttribLocation(program, "a_height");

    glGenBuffers(2, vertex_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) + sizeof(heightDataForGPU) * 2, vertexData, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat) + sizeof(heightDataForGPU), sizeof(heightDataForGPU), heightDataForGPU); //just in case, when heightDataForGPU all 0

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLshort), indicesData, GL_STATIC_DRAW);
    printf("Vertice Count: %d  Indices Count: %d\n", vertexCount, indicesCount);
    //printf("%f %f %f\n", vertexData[0], vertexData[1], vertexData[2]);
    //printf("%u %u %u\n", indicesData[0], indicesData[1], indicesData[2]);

    glVertexAttribPointer(a_position_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glVertexAttribPointer(a_height_location, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (void *)(vertexCount * sizeof(GLfloat)));
    glEnableVertexAttribArray(a_position_location);
    glEnableVertexAttribArray(a_height_location);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

    Matrix_Perspective(projectionMatrix, 45, (float)CANVAS_WIDTH / (float)CANVAS_HEIGHT, 0.1f, 100);

    return 0;
}
float angle;

int Render(AppContext *context)
{
    angle += 1;
    if (angle > 360)
    {
        angle -= 360;
    }

    GetData();
    //to-do: replace with fft result
    /*
    for (int i = 0; i < FREQ_COUNT; i++)
    {
        heightData[i] += 0.1f;
        if (heightData[i] > 1.0f)
            heightData[i] = 0;
    }
    PortData();
    */

    Matrix_IdentityFunction(modelViewMatrix);
    Matrix_RotateY(modelViewMatrix, angle);
    Matrix_Translate(modelViewMatrix, 0.0f, -1.0f, -5.0f);

    glClearColor(0, 0, 0.3f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(u_projection_location, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(u_modelView_location, 1, GL_FALSE, modelViewMatrix);

    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, 0);
    return 0;
}
