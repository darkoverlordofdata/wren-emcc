# wren emcc


## emscripten first
wren bindings designed to work on emscripten

## gui
nuklear works with emscripten using SDL2 and GLES2. So that makes up my mind. That's fine, glfw3 requires stb_image and other additional librries.


## libuv
other wren based projects use libuv, but I want to be emscripten first - libuv doesn't work (https://github.com/libuv/help/issues/128) in emscripten.

proposed solutions:
* use libuv on desktop and libuv-em on emscripten?
* use 1 new api that works on either desktop or browser?

