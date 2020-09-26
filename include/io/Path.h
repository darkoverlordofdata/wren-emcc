#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>

void io_path_Allocate(WrenVM* vm);
void io_path_Finalize(void* data);
void io_path_Absolute(WrenVM* vm);
void io_path_Relative(WrenVM* vm);
void io_path_Simple(WrenVM* vm);
void io_path_Cwd(WrenVM* vm);
void io_path_Type(WrenVM* vm);
void io_path_DirName(WrenVM* vm);
void io_path_RemoveExtension(WrenVM* vm);
void io_path_Join(WrenVM* vm);
void io_path_AppendChar(WrenVM* vm);
void io_path_AppendString(WrenVM* vm);
void io_path_Normalize(WrenVM* vm);
void io_path_ToString(WrenVM* vm);
