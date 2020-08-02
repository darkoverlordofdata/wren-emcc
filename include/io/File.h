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
// #include <linux/limits.h>
#define PATH_MAX 4096
#define GetCwd getcwd
#endif
#include "wren/path.h"


/**
 *  io/file::Allocate
 */
void io_file_Allocate(WrenVM* vm);
void io_file_Finalize(void* data);
