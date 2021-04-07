cd %*
call _c.bat
cd ..

rd /Q /S E:\LocalHost\wwwroot\wasm
md E:\LocalHost\wwwroot\wasm
cd debug
for %%f in (*.html *.js *.wasm *.data) do (

copy %%f E:\LocalHost\wwwroot\wasm\

)
cd ..
echo Updated