#pragma once
#include "tglm/tglm.h"
#include <GL/gl.h>
#include <corefw/class.h>

/**
 * class DNATexture2D
 */
typedef struct DNATexture2D DNATexture2D;
extern const CFWClass* DNATexture2DClass;

extern overloadable void* New(DNATexture2D* this, GLuint internalFormat, GLuint imageFormat, char* path);

extern overloadable void Generate(
    DNATexture2D* this,
    GLuint width,
    GLuint height,
    unsigned char* data);

extern overloadable void Bind(const DNATexture2D* this);

extern overloadable char* ToString(const DNATexture2D* this);
