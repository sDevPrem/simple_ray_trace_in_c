# Simple Ray Tracing In 

## Preview
[Preview](https://github.com/user-attachments/assets/ed6cec3e-7728-4d23-9d32-43ca1ccd6c95)

## Reference
https://youtu.be/2BLRLuczykM?si=6m5ffWuxGBVcr3OV

## To compile

```bash
//mac
SDL_PATH=/opt/homebrew
gcc -o ray_trace ray_trace.c circle_utils.c -lSDL2 -lm -I${SDL_PATH}/include -D_THREAD_SAFE -L/${SDL_PATH}/lib

//windows
set SDL_PATH=C:\path\to\SDL2  // Replace with the actual path
gcc -o ray_trace ray_trace.c circle_utils.c -lSDL2 -lm -I"%SDL_PATH%\include" -L"%SDL_PATH%\lib"

gcc -o ray_trace ray_trace.c circle_utils.c -lSDL2 -lm -I/opt/homebrew/include -D_THREAD_SAFE -L/opt/homebrew/lib
```

## To run

```bash
./ray_trace
```