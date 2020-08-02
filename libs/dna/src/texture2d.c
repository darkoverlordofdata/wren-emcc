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
#include "stb_image.h"
#include "texture2d-private.h"
#include <GLFW/glfw3.h>

corefw(DNATexture2D);

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

/**
 *  DNATexture2D Constructor
 * 
 * @param internalFormat
 * @param imageFormat
 * @param path to image
 */
method void* New(DNATexture2D* this, GLuint internalFormat, GLuint imageFormat, char* path)
{
    // DNATexture2D* this = cfw_new((CFWClass*)DNATexture2DClass);
    this->path = cfw_strdup(path);
    this->Width = 0;
    this->Height = 0;
    this->wrapS = GL_REPEAT;
    this->wrapT = GL_REPEAT;
    this->filterMin = GL_LINEAR;
    this->filterMag = GL_LINEAR;
    this->InternalFormat = internalFormat;
    this->ImageFormat = imageFormat;
    glGenTextures(1, &this->Id);
    return this;
}

/**
 * Generate
 * 
 * @param width of image to generate
 * @param height of image to generate
 * @param data bitmap data
 * 
 */
method void Generate(
    DNATexture2D* this,
    GLuint width,
    GLuint height,
    unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->Id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Bind
 * 
 * binds the texture to GL
 */
method void Bind(const DNATexture2D* this)
{
    glBindTexture(GL_TEXTURE_2D, this->Id);
}

method char* ToString(const DNATexture2D* this)
{
    char* s = calloc(1024, 1);
    return s;
}
