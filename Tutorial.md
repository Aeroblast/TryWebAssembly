# WebAssembly
[About Emscripten](https://emscripten.org/docs/introducing_emscripten/about_emscripten.html)

Emscripten: Open Source compiler toolchain to WebAssembly

Generate fast and small WebAssembly and run it on the Web

C/C++ Code => Emscripten LLVM => WebAssembly/asm.js

例: Unreal Engine 4, Unity

# Prepare
[Download and install](https://emscripten.org/docs/getting_started/downloads.html)
指示通りやれば大丈夫だと思う（

# Compile
Emscripten Compiler Frontend (emcc)

* Windows should use emcmdprompt.bat, which sets environment variables.

[](https://emscripten.org/docs/compiling/Building-Projects.html#emscripten-linker-output-files)
+ `emcc hello_world.c` => wasm js
+ `emcc hello_world.c -o hello.html` => wasm js html

SDL、OpenGLなどのlibを使いたいときは
`-s USE_WEBGL2=1 `
`-s USE_SDL=2 `
つける。

# Debug
emrunというコマンドはあるが、なぜかエラー出てる：OSError: [WinError 10013] 以一种访问权限不允许的方式做了一个访问套接字的尝试。
It seems like there is some permission problem.

Any server that serves static file is ok. So just pick one.

# About this repository
自分用にいくつかのbatchをかいた。`_u.bat`での`E:\LocalHost\wwwroot\wasm\`をサーバーのstatic file directoryにかえてください。

1. Start with `emcmdprompt.bat`
2. `_u FreqView` or `_u Spirit2D` Compile to 'debug' directory and copy to server directory. 