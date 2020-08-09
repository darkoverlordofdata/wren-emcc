# wren emcc

experimental wren bindings designed to work on emscripten

### emscripten first
for me, it's a great fit. emscripten uses clang, and I like to use clang extensions.

other wren based projects use libuv, but I want to be emscripten first - libuv doesn't work (https://github.com/libuv/help/issues/128) in emscripten.

proposed solutions:
* use libuv on desktop and libuv-em on emscripten?
* use 1 new api that works on either desktop or browser?

### vectors and overloads and lambdas oh my
clang extensions this project uses:
* vectors: __attribute__((ext_vector_type(n)))
* overloads: __attribute__(overloadable))
* lambdas: -fblocks -lBlocksRuntime
   - curryed bindings. yum.

not implemented:
* matrices: __attribute__((matrix_type(4, 4)))
   - doesn't compile using emcc
   - mat4x4 emulated as ext_vector_type(16)

### I Want A New C...
Lambdas and a few macro's can make c seem like a modern language. Add CoreFW for memory management and object base.

```c
#define var __auto_type
#define overloadable __attribute__((overloadable))

CFWMap* map = cfw_create(cfw_map, NULL);
...
ForEach(map, ^(void* key, void* item){ 
   printf("%s -- %s\n", cstr(key), cstr(item));
});


```