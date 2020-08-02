#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wren.h>
#ifdef _WIN32
#include <direct.h>
#include <limits.h>
#define GetCwd _getcwd
#define PATH_MAX MAX_PATH
#else
#define PATH_MAX 4096
#define GetCwd getcwd
#endif
#include "wren/path.h"

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
void io_path_AppemdString(WrenVM* vm);
void io_path_Normalize(WrenVM* vm);
void io_path_ToString(WrenVM* vm);
