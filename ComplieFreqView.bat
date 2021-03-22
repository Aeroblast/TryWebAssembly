".\emsdk\upstream\emscripten\emcc" ^
-Iinclude ^
FreqView\matrix.c ^
FreqView\render.c ^
FreqView\gen_vertex.c ^
FreqView\Main.c ^
--preload-file data ^
-s WASM=1 -s USE_WEBGL2=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 ^
-s SDL2_IMAGE_FORMATS=["png"] ^
-o debug\app.js