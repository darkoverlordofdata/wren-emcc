#!/bin/bash
#
#   compile the static wren lib for emscripten   
#

emcc   -r -std=c11                                  \
    external/blocksruntime/BlocksRuntime/runtime.c  \
    external/blocksruntime/BlocksRuntime/data.c     \
    -Iexternal/blocksruntime                        \
    -Iexternal/blocksruntime/BlocksRuntime          \
    -o libs/libBlocksRuntime.bc

cd external/corefw

#
#   compile the static wren lib for emscripten   
#
emcc   -r -std=c11                      \
       external/corefw/src/array.c		\
       external/corefw/src/bool.c		\
       external/corefw/src/box.c		\
       external/corefw/src/class.c		\
       external/corefw/src/double.c		\
       external/corefw/src/file.c		\
       external/corefw/src/int.c		\
       external/corefw/src/map.c		\
       external/corefw/src/object.c		\
       external/corefw/src/range.c		\
       external/corefw/src/refpool.c    \
       external/corefw/src/stream.c		\
       external/corefw/src/string.c		\
       external/corefw/src/tcpsocket.c  \
        -o libs/libcorefw.bc


#
#   compile the static wren lib for emscripten   
#
emcc   -r -std=c11                      \
        libs/wren/optional/wren_opt_meta.c \
        libs/wren/optional/wren_opt_random.c \
        libs/wren/vm/wren_compiler.c \
        libs/wren/vm/wren_core.c \
        libs/wren/vm/wren_debug.c \
        libs/wren/vm/wren_primitive.c \
        libs/wren/vm/wren_utils.c \
        libs/wren/vm/wren_value.c \
        libs/wren/vm/wren_vm.c \
        -Ilibs/wren/include \
        -Ilibs/wren/vm \
        -Ilibs/wren/optional \
        -o libs/libwren.bc


