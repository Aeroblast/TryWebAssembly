#include <stdio.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //SDL2找不到不管 编译才有\emsdk\upstream\emscripten\cache\wasm

#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600
#define FLOAT32_BYTE_SIZE 4
#define STRIDE FLOAT32_BYTE_SIZE * 4

Uint32 currentTime, lastTime;
SDL_Event event;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *sprite_texture;
SDL_Surface *sprite_surface;
int sprite_width;
int sprite_height;
float ship_x = 0.0;
float ship_y = 0.0;

GLuint program = 0;
GLuint texture;
GLint a_texcoord_location = -1;
GLint a_position_location = -1;
GLint u_texture_location = -1;
GLint u_texture2_location = -1;
GLint u_translate_location = -1;
GLuint vertex_texture_buffer;

float vertex_texture_data[] = {
	// x,   y,        u,   v
	400.0 / CANVAS_WIDTH, 400.0 / CANVAS_HEIGHT, 1.0, 0.0,
	-400.0 / CANVAS_WIDTH, 400.0 / CANVAS_HEIGHT, 0.0, 0.0,
	400.0 / CANVAS_WIDTH, -400.0 / CANVAS_HEIGHT, 1.0, 1.0,
	-400.0 / CANVAS_WIDTH, -400.0 / CANVAS_HEIGHT, 0.0, 1.0,
	400.0 / CANVAS_WIDTH, -400.0 / CANVAS_HEIGHT, 1.0, 1.0,
	-400.0 / CANVAS_WIDTH, 400.0 / CANVAS_HEIGHT, 0.0, 0.0

};
const GLchar *vertex_shader_code[] = {"precision mediump float; \n"
									  "attribute vec4 a_position; \n"
									  "attribute vec2 a_texcoord; \n"
									  "uniform vec4 u_translate; \n"
									  "varying vec2 v_texcoord; \n"
									  "void main() { \n"
									  "gl_Position = u_translate + a_position; \n"
									  "v_texcoord = a_texcoord; \n"
									  "} \n"};
const GLchar *fragment_shader_code[] = {"precision mediump float; \n"
										"varying vec2 v_texcoord; \n"
										"uniform sampler2D u_texture; \n"
										"void main() { \n"
										"gl_FragColor = texture2D(u_texture, v_texcoord); \n"
										"} \n"};

void Update(void)
{

	currentTime = SDL_GetTicks();
	Uint32 deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform4f(u_translate_location, -0.5, ship_y, 0, 0);
	glUniform1i(u_texture_location, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUniform4f(u_translate_location, 0.5, ship_y, 0, 0);
	glUniform1i(u_texture_location, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//return EM_TRUE;
}
// Shader sources

int Start(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(0, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, (SDL_WINDOW_OPENGL));
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
	SDL_RenderClear(renderer);
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
	glUseProgram(program);
	u_texture_location = glGetUniformLocation(program, "u_texture");
	u_translate_location = glGetUniformLocation(program, "u_translate");
	a_position_location = glGetAttribLocation(program, "a_position");
	a_texcoord_location = glGetAttribLocation(program, "a_texcoord");
	glGenBuffers(1, &vertex_texture_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_texture_data), vertex_texture_data, GL_STATIC_DRAW);
	GLuint circle_tex, normal_tex;
	glGenTextures(1, &circle_tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, circle_tex);
	SDL_Surface *surface;
	surface = IMG_Load("/data/Test1.png");
	if (!surface)
	{
		printf("failed to load image: %s\n", IMG_GetError());
		return 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glUniform1i(u_texture_location, 0);
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(surface);
	glGenTextures(1, &normal_tex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal_tex);
	surface = IMG_Load("/data/Test0.png");
	if (!surface)
	{
		printf("failed to load image: %s\n", IMG_GetError());
		return 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glUniform1i(u_texture2_location, 1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(surface);

	glEnableVertexAttribArray(a_position_location);
	glVertexAttribPointer(a_position_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(a_texcoord_location);
	glVertexAttribPointer(a_texcoord_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	return 0;
}
int main()
{
	printf("Just test\n");
	emscripten_set_main_loop(Update, 0, 0);
	Start();
}