rd /Q /S docs\demo
md docs\demo
cd debug
for %%f in (*.html *.js *.wasm *.data) do (

copy %%f ..\docs\demo\

)