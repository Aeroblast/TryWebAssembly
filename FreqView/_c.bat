copy container.html ..\debug\debug.html
"..\emsdk\upstream\emscripten\emcc" ^
-Iinclude ^
matrix.c ^
render.c ^
gen_vertex.c ^
Main.c ^
-s WASM=1 -s USE_WEBGL2=1 -s USE_SDL=2 ^
-s EXPORTED_FUNCTIONS="['_main','_GetArrayHEAP']" ^
-o ..\debug\app.js