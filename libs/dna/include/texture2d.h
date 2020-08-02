#pragma once
#include "tglm.h"
#include <GL/gl.h>
#include <corefw/class.h>

/**
 * class DNATexture2D
 */
typedef struct DNATexture2D DNATexture2D;
extern const CFWClass* DNATexture2DClass;

extern method void* New(DNATexture2D* this, GLuint internalFormat, GLuint imageFormat, char* path);

extern method void Generate(
    DNATexture2D* this,
    GLuint width,
    GLuint height,
    unsigned char* data);

extern method void Bind(const DNATexture2D* this);

extern method char* ToString(const DNATexture2D* this);
