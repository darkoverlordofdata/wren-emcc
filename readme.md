# wren emcc


## emscripten first
wren bindings designed to work on emscripten

## gui
nuklear works with emscripten using SDL2 and GLES2. The alternative is glfw+stb etc., so it has some advantages when loading resources.


## libuv
other wren based projects use libuv, but I want to be emscripten first - libuv doesn't work (https://github.com/libuv/help/issues/128) in emscripten.

proposed solutions:
* use libuv on desktop and libuv-em on emscripten?
* use 1 new api that works on either desktop or browser?

