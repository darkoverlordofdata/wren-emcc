#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>
#include <tglm/tglm.h>

void math_vec4_allocate(WrenVM* vm) 
{ 
    float* data = (float*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(float[4]));
    data[0] = wrenGetSlotDouble(vm, 1);
    data[1] = wrenGetSlotDouble(vm, 2);
    data[2] = wrenGetSlotDouble(vm, 3);
    data[3] = wrenGetSlotDouble(vm, 4);
}

void math_vec4_finalize(void* data) { }

void math_vec4_get_x(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[0]);
}

void math_vec4_set_x(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[0] = wrenGetSlotDouble(vm, 0);
}

void math_vec4_get_y(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[1]);
}

void math_vec4_set_y(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[1] = wrenGetSlotDouble(vm, 0);
}

void math_vec4_get_z(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[2]);
}

void math_vec4_set_z(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[2] = wrenGetSlotDouble(vm, 0);
}

void math_vec4_get_w(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, data[3]);
}

void math_vec4_set_w(WrenVM* vm) 
{ 
    float* data = wrenGetSlotForeign(vm, 0);
    data[3] = wrenGetSlotDouble(vm, 0);
}

void math_vec4_clamp(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec4 v = { data[0], data[1], data[2] , data[3] };
    float a = wrenGetSlotDouble(vm, 1);
    float b = wrenGetSlotDouble(vm, 2);
    v = glm_clamp(v, a, b);
    data[0] = v.x;
    data[1] = v.y;
    data[2] = v.z;
    data[4] = v.z;
}

void math_vec4_dot(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec4 a = { data[0], data[1], data[2] , data[3] };

    float* datb = wrenGetSlotForeign(vm, 1);
    Vec4 b = { datb[0], datb[1], datb[2], datb[3] };

    wrenSetSlotDouble(vm, 0, glm_dot(a, b));
}

void math_vec4_length(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec4 a = { data[0], data[1], data[2] , data[3] };

    wrenSetSlotDouble(vm, 0, glm_length(a));
}

void math_vec4_norm(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec4 a = { data[0], data[1], data[2] , data[3] };

    wrenSetSlotDouble(vm, 0, glm_norm(a));
}

void math_vec4_norm2(WrenVM* vm)
{
    float* data = wrenGetSlotForeign(vm, 0);
    Vec4 a = { data[0], data[1], data[2] , data[3] };

    wrenSetSlotDouble(vm, 0, glm_norm2(a));

}

