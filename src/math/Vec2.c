#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>
#include <dna.h>

void math_vec2_allocate(WrenVM* vm) 
{ 
    float* data = (float*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(float[2]));
    data[0] = wrenGetSlotDouble(vm, 1);
    data[1] = wrenGetSlotDouble(vm, 2);
}

void math_vec2_finalize(void* data) { }

void math_vec2_get_x(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[0]);
}

void math_vec2_set_x(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[0] = wrenGetSlotDouble(vm, 0);
}

void math_vec2_get_y(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[1]);
}

void math_vec2_set_y(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[1] = wrenGetSlotDouble(vm, 0);
}

void math_vec2_clamp(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 v = { data[0], data[1] };
    float a = wrenGetSlotDouble(vm, 1);
    float b = wrenGetSlotDouble(vm, 2);
    v = glm_clamp(v, a, b);
    data[0] = v.x;
    data[1] = v.y;
}

void math_vec2_dot(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 a = { data[0], data[1] };

    float* datb = wrenGetSlotForeign(vm, 1);
    Vec2 b = { datb[0], datb[1] };

    wrenSetSlotDouble(vm, 0, glm_dot(a, b));
}

void math_vec2_length(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 a = { data[0], data[1] };

    wrenSetSlotDouble(vm, 0, glm_length(a));
}

void math_vec2_norm(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 a = { data[0], data[1] };

    wrenSetSlotDouble(vm, 0, glm_norm(a));
}

void math_vec2_norm2(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 a = { data[0], data[1] };

    wrenSetSlotDouble(vm, 0, glm_norm2(a));
}

void math_vec2_normalize(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec2 v = { data[0], data[1] };

    v = glm_normalize(v);
    data[0] = v.x;
    data[1] = v.y;
}

