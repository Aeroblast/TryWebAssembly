#include <GLES3/gl3.h>
const GLchar *vertex_shader_code[] = {"precision mediump float; \n"
                                      "attribute vec4 a_position; \n"
                                      "attribute vec2 a_texcoord; \n"
                                      "varying vec2 v_texcoord; \n"
                                      "uniform mat4 u_projection;\n"
                                      "uniform mat4 u_modelView;\n"
                                      "void main() { \n"
                                      "    gl_Position = u_projection * u_modelView * a_position;\n"
                                      "    v_texcoord = a_texcoord;\n"
                                      "} \n"};
const GLchar *fragment_shader_code[] = {"precision mediump float; \n"
                                        "varying vec2 v_texcoord; \n"
                                        "uniform sampler2D u_texture; \n"
                                        "void main() { \n"
                                        "gl_FragColor = texture2D(u_texture, v_texcoord)+vec4(0.5,0.5,0.5,1); \n"
                                        "} \n"};
GLfloat vertices[] = {-1.0f, 1.0f, -1.0f, /* Back. */
                      1.0f, 1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, 1.0f, 1.0f, /* Front. */
                      1.0f, 1.0f, 1.0f,
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f, -1.0f, /* Left. */
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, -1.0f, /* Right. */
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      -1.0f, -1.0f, -1.0f, /* Top. */
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f, /* Bottom. */
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, -1.0f,
                      /*uv*/
                      1.0f, 1.0f, /* Back. */
                          0.0f, 1.0f,
                          1.0f, 0.0f,
                          0.0f, 0.0f,
                          0.0f, 1.0f, /* Front. */
                          1.0f, 1.0f,
                          0.0f, 0.0f,
                          1.0f, 0.0f,
                          0.0f, 1.0f, /* Left. */
                          0.0f, 0.0f,
                          1.0f, 0.0f,
                          1.0f, 1.0f,
                          1.0f, 1.0f, /* Right. */
                          1.0f, 0.0f,
                          0.0f, 0.0f,
                          0.0f, 1.0f,
                          0.0f, 1.0f, /* Top. */
                          0.0f, 0.0f,
                          1.0f, 0.0f,
                          1.0f, 1.0f,
                          0.0f, 0.0f, /* Bottom. */
                          0.0f, 1.0f,
                          1.0f, 1.0f,
                          1.0f, 0.0f  
                      };

GLushort indices[] = {0, 2, 3, 0, 1, 3, 4, 6, 7, 4, 5, 7, 8, 9, 10, 11, 8, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22};