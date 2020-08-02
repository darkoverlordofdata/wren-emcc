#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>

void math_vec2_allocate(WrenVM* vm);
void math_vec2_finalize(void* data);
void math_vec2_get_x(WrenVM* vm);
void math_vec2_set_x(WrenVM* vm);
void math_vec2_get_y(WrenVM* vm);
void math_vec2_set_y(WrenVM* vm);
void math_vec2_clamp(WrenVM* vm);
void math_vec2_dot(WrenVM* vm);
void math_vec2_length(WrenVM* vm);
void math_vec2_norm(WrenVM* vm);
void math_vec2_norm2(WrenVM* vm);
void math_vec2_normalize(WrenVM* vm);

