#pragma once
#include <stdio.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include "dna.h"
#include "cfw.h"
#include <GLFW/glfw3.h>

/**
 *  class DNAResourceManager
 */
struct DNAResourceManager {
    CFWObject obj;
    CFWMap* Shaders;
    CFWMap* Textures;
    CFWMap* Fonts;
};
