#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include "tglm/tglm.h"
#include <GLFW/glfw3.h>
#include <corefw/class.h>

typedef struct DNAShader DNAShader;
extern const CFWClass* DNAShaderClass;

extern overloadable DNAShader* Use(DNAShader* this);

extern overloadable void* New(DNAShader* this, CFWString* vShader, CFWString* fShader);
extern overloadable GLuint GetId(DNAShader* this);
extern overloadable void Compile(DNAShader* this, const GLchar* vertexSource, const GLchar* fragmentSource);
extern overloadable void SetFloat(
    DNAShader* this,
    const GLchar* name,
    const GLfloat value,
    const GLboolean useShader);

extern overloadable void SetInteger(
    DNAShader* this,
    const GLchar* name,
    GLint value,
    GLboolean useShader);

extern overloadable void SetInteger(
    DNAShader* this,
    const GLchar* name,
    GLint value);

extern overloadable void SetVector2(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLboolean useShader);

extern overloadable void SetVector2(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y);

extern overloadable void SetVector2v(
    DNAShader* this,
    const GLchar* name,
    const Vec2* vector,
    GLboolean useShader);

extern overloadable void SetVector2v(
    DNAShader* this,
    const GLchar* name,
    const Vec2* vector);

extern overloadable void SetVector3(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLboolean useShader);

extern overloadable void SetVector3(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z);

extern overloadable void SetVector3v(
    DNAShader* this,
    const GLchar* name,
    const Vec3* vector,
    GLboolean useShader);

extern overloadable void SetVector3v(
    DNAShader* this,
    const GLchar* name,
    const Vec3* vector);

extern overloadable void SetVector4(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w,
    GLboolean useShader);

extern overloadable void SetVector4(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w);

extern overloadable void SetVector4v(
    DNAShader* this,
    const GLchar* name,
    const Vec4* vector,
    GLboolean useShader);

extern overloadable void SetVector4v(
    DNAShader* this,
    const GLchar* name,
    const Vec4* vector);

extern overloadable void SetMatrix(
    DNAShader* this,
    const GLchar* name,
    const Mat* matrix,
    GLboolean useShader);

extern overloadable void SetMatrix(
    DNAShader* this,
    const GLchar* name,
    const Mat* matrix);
