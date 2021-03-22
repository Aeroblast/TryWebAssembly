#include <GLES3/gl3.h>
const GLchar *vertex_shader_code[] = {"precision mediump float; \n"
                                      "attribute vec4 a_position; \n"
                                      "attribute float a_height; \n"
                                      "uniform mat4 u_projection;\n"
                                      "uniform mat4 u_modelView;\n"
                                      "varying float v_y; \n"
                                      "void main() { \n"
                                      "    vec4 temp=a_position;"
                                      "    float height = a_height;"
                                      "    temp.y *= ((height + 0.1) * 1.0);\n"
                                      "    gl_Position = u_projection * u_modelView * temp;\n"
                                      "    v_y=a_position.y;"
                                      "} \n"};
const GLchar *fragment_shader_code[] = {"precision mediump float; \n"
                                        "varying float v_y; \n"
                                        "void main() { \n"
                                        "gl_FragColor =vec4(0.1+0.9*v_y,0.7,0.7,1); \n"
                                        "} \n"};