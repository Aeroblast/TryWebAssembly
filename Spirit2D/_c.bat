copy debug.html ..\debug\debug.html
"..\emsdk\upstream\emscripten\emcc" ^
Main.c ^
--preload-file data ^
-s WASM=1 -s USE_WEBGL2=1 -s USE_SDL=2 ^
-s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=["png"] ^
-o ..\debug\app.js