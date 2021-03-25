#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#include "shared.h"
struct Actor
{

    GLuint program;
    GLchar **const *p_vertex_shader_code;
    GLchar **const *p_fragment_shader_code;

    GLuint u_texture;
    GLint a_texcoord_location;
    GLint a_position_location;
    GLint u_texture_location;
    GLint u_modelView_location;
    GLint u_projection_location;

    char *textureFilename;
    int textureWidth;
    int textureHeight;
    GLuint textureIndex;
    int (*Init)(Actor *, AppContext *);
    int (*Update)(Actor *, AppContext *);

    float modelViewMatrix[16];
};
int Actor_Init(Actor *obj, AppContext *context);
int Actor_Render(Actor *obj, AppContext *context);