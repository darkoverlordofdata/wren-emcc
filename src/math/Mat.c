#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>
// #include <dna.h>
#include <tglm/tglm.h>
void math_mat_allocate(WrenVM* vm) 
{ 
    float* data = wrenSetSlotNewForeign(vm, 0, 0, sizeof(float[16]));
    for (int i=0; i<16; i++) data[i] = 0;
}

void math_mat_finalize(void* data) { }

void math_mat_get(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    int row = (int)wrenGetSlotDouble(vm, 1);
    int col = (int)wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, data[row*4+col]);
}

void math_mat_set(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    int row = (int)wrenGetSlotDouble(vm, 1);
    int col = (int)wrenGetSlotDouble(vm, 2);
    data[row*4+col] = wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, data[row*4+col]);

}

void math_mat_identity(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Mat m = mat_identity();
    for (int i=0; i<16; i++) data[i] = m[i];
}

void math_mat_scale(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Mat m = { 0 };
    for (int i=0; i<16; i++) m[i] = data[i];

    float* datb = wrenGetSlotForeign(vm, 1);
    Vec3 b = { datb[0], datb[1], datb[2] };

    m = glm_scale(m, b);
    for (int i=0; i<16; i++) data[i] = m[i];
}

void math_mat_ortho(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);

    float left = wrenGetSlotDouble(vm, 1);
    float right = wrenGetSlotDouble(vm, 2);
    float bottom = wrenGetSlotDouble(vm, 3);
    float top = wrenGetSlotDouble(vm, 4);
    float nearVal = wrenGetSlotDouble(vm, 5);
    float farVal = wrenGetSlotDouble(vm, 6);

    Mat m  = glm_ortho(left, right, bottom, top, nearVal, farVal);
    for (int i=0; i<16; i++) data[i] = m[i];
}

void math_mat_rotate(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Mat m = { 0 };
    for (int i=0; i<16; i++) m[i] = data[i];

    float angle = wrenGetSlotDouble(vm, 1);

    float* datb = wrenGetSlotForeign(vm, 2);
    Vec3 b = { datb[0], datb[1], datb[2] };

    m = glm_rotate(m, angle, b);
    for (int i=0; i<16; i++) data[i] = m[i];
}



