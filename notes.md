## experimental stuff ...
experimental wren bindings designed to work on emscripten

### emscripten first
for me, it's a great fit. emscripten uses clang, and I like to use clang extensions.

But all these cool things have a price - undefined behaviour, the bane of c. 
So the the original code is now branched to 'experimental' and all the following cool stuff will be replaced with boring code. 

1. vectors: use limmath.h
2. overloads: use custom name mangling
3. lambdas: use context struc

this removes blocksruntime plus a bunch of macros and attributes

### vectors and overloads and lambdas oh my
clang extensions this project uses:
* vectors: __attribute__((ext_vector_type(n)))
* overloads: __attribute__(overloadable))
* lambdas: -fblocks -lBlocksRuntime
   - curryed bindings. yum.


