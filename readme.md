# wren emcc

wren bindings designed to work on emscripten

emscripten uses clang, and I like to use clang extensions.

this project uses:
* vectors: __attribute__((ext_vector_type(4)))
* overloads: __attribute__(overloadable))
* lambdas: -fblocks -lBlocksRuntime

not implemented:
* matrices: __attribute__((matrix_type(4, 4)))
   - doesn't compile using emcc
   - mat4x4 emulated as ext_vector_type(16)

