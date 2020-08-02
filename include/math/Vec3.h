#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>

void math_vec3_allocate(WrenVM* vm);
void math_vec3_finalize(void* data);
void math_vec3_get_x(WrenVM* vm);
void math_vec3_set_x(WrenVM* vm);
void math_vec3_get_y(WrenVM* vm);
void math_vec3_set_y(WrenVM* vm);
void math_vec3_get_z(WrenVM* vm);
void math_vec3_set_z(WrenVM* vm);
void math_vec3_clamp(WrenVM* vm);
void math_vec3_dot(WrenVM* vm);
void math_vec3_length(WrenVM* vm);
void math_vec3_norm(WrenVM* vm);
void math_vec3_norm2(WrenVM* vm);
void math_vec3_normalize(WrenVM* vm);

