#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include "tglm.h"
#include <GLFW/glfw3.h>
#include <corefw/class.h>

typedef struct DNAShader DNAShader;
extern const CFWClass* DNAShaderClass;

extern method DNAShader* Use(DNAShader* this);

extern method void* New(DNAShader* this, CFWString* vShader, CFWString* fShader);
extern method GLuint GetId(DNAShader* this);
extern method void Compile(DNAShader* this, const GLchar* vertexSource, const GLchar* fragmentSource);
extern method void SetFloat(
    DNAShader* this,
    const GLchar* name,
    const GLfloat value,
    const GLboolean useShader);

extern method void SetInteger(
    DNAShader* this,
    const GLchar* name,
    GLint value,
    GLboolean useShader);

extern method void SetInteger(
    DNAShader* this,
    const GLchar* name,
    GLint value);

extern method void SetVector2(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLboolean useShader);

extern method void SetVector2(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y);

extern method void SetVector2v(
    DNAShader* this,
    const GLchar* name,
    const Vec2* vector,
    GLboolean useShader);

extern method void SetVector2v(
    DNAShader* this,
    const GLchar* name,
    const Vec2* vector);

extern method void SetVector3(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLboolean useShader);

extern method void SetVector3(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z);

extern method void SetVector3v(
    DNAShader* this,
    const GLchar* name,
    const Vec3* vector,
    GLboolean useShader);

extern method void SetVector3v(
    DNAShader* this,
    const GLchar* name,
    const Vec3* vector);

extern method void SetVector4(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w,
    GLboolean useShader);

extern method void SetVector4(
    DNAShader* this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w);

extern method void SetVector4v(
    DNAShader* this,
    const GLchar* name,
    const Vec4* vector,
    GLboolean useShader);

extern method void SetVector4v(
    DNAShader* this,
    const GLchar* name,
    const Vec4* vector);

extern method void SetMatrix(
    DNAShader* this,
    const GLchar* name,
    const Mat* matrix,
    GLboolean useShader);

extern method void SetMatrix(
    DNAShader* this,
    const GLchar* name,
    const Mat* matrix);
