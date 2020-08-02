#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>

void math_vec4_allocate(WrenVM* vm);
void math_vec4_finalize(void* data);
void math_vec4_get_x(WrenVM* vm);
void math_vec4_set_x(WrenVM* vm);
void math_vec4_get_y(WrenVM* vm);
void math_vec4_set_y(WrenVM* vm);
void math_vec4_get_z(WrenVM* vm);
void math_vec4_set_z(WrenVM* vm);
void math_vec4_get_w(WrenVM* vm);
void math_vec4_set_w(WrenVM* vm);
void math_vec4_clamp(WrenVM* vm);
void math_vec4_dot(WrenVM* vm);
void math_vec4_length(WrenVM* vm);
void math_vec4_norm(WrenVM* vm);
void math_vec4_norm2(WrenVM* vm);

