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
#include <GLFW/glfw3.h>

#include "dna.h"
#include "cfw.h"

/**
 *  class DNAElementRenderer
 */
struct DNAElementRenderer {
    CFWObject obj;
    struct DNAShader* shader;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
};
