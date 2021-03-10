#include <GLES2/gl2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "matrix.h"
#include "shared.h"
#include "Actor.h"
#include "data.h"
float projectionMatrix[16];

GLuint vertex_buffers[2];
int Actor_Init(Actor *obj, AppContext *context)
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
    obj->program = glCreateProgram();
    glAttachShader(obj->program, vertex_shader);
    glAttachShader(obj->program, fragment_shader);
    glLinkProgram(obj->program);
    GLint link_success = 0;
    glGetProgramiv(obj->program, GL_LINK_STATUS, &link_success);
    if (link_success == GL_FALSE)
    {
        printf("failed to link program\n");
        glDeleteProgram(obj->program);
        return 0;
    }
    glUseProgram(obj->program);
    obj->u_texture_location = glGetUniformLocation(obj->program, "u_texture");
    obj->u_modelView_location = glGetUniformLocation(obj->program, "u_modelView");
    obj->u_projection_location = glGetUniformLocation(obj->program, "u_projection");
    obj->a_position_location = glGetAttribLocation(obj->program, "a_position");
    obj->a_texcoord_location = glGetAttribLocation(obj->program, "a_texcoord");

    glGenBuffers(2, vertex_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint textureId;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    SDL_Texture *sprite_texture;
    SDL_Surface *sprite_surface;
    sprite_surface = IMG_Load(obj->textureFilename);
    if (!sprite_surface)
    {
        printf("failed to load image: %s\n", IMG_GetError());
        return 0;
    }
    sprite_texture = SDL_CreateTextureFromSurface(context->renderer, sprite_surface);
    if (!sprite_texture)
    {
        printf("failed to create texture: %s\n", IMG_GetError());
        return 0;
    }
    SDL_QueryTexture(sprite_texture, NULL, NULL, &obj->textureWidth, &obj->textureHeight);
    printf("%d %d\n", obj->textureWidth, obj->textureHeight);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, obj->textureWidth, obj->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite_surface->pixels);
    SDL_FreeSurface(sprite_surface);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    Matrix_Perspective(projectionMatrix, 45, (float)800 / (float)600, 0.1f, 100);
    return 0;
}



int Actor_Render(Actor *obj, AppContext *context)
{
    glUseProgram(obj->program);
    glVertexAttribPointer(obj->a_position_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(obj->a_position_location);
    glVertexAttribPointer(obj->a_texcoord_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)(72 * sizeof(GLfloat)));
    glEnableVertexAttribArray(obj->a_texcoord_location);
    glUniformMatrix4fv(obj->u_projection_location, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(obj->u_modelView_location, 1, GL_FALSE, obj->modelViewMatrix);
    glUniform1i(obj->u_texture_location, 0);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
    return 0;
}
