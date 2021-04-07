rd /Q /S E:\LocalHost\wwwroot\wasm
md E:\LocalHost\wwwroot\wasm
cd debug
for %%f in (*.html *.js *.wasm *.data) do (

copy %%f E:\LocalHost\wwwroot\wasm\

)
start "" http://localhost:19191/wasm/debug.html
dotnet run --project E:\LocalHost