#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>

void math_mat_allocate(WrenVM* vm);
void math_mat_finalize(void* data);

void math_mat_identity(WrenVM* vm);
void math_mat_scale(WrenVM* vm);
void math_mat_ortho(WrenVM* vm);
void math_mat_rotate(WrenVM* vm);
void math_mat_get(WrenVM* vm);
void math_mat_set(WrenVM* vm);
