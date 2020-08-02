#include <stdio.h>
#include <string.h>
#include <unistd.h>
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
#include "io/File.h"

/**
 *  io/file::Allocate
 */
void io_file_Allocate(WrenVM* vm) 
{ 
   //  FILE** file = (FILE**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(FILE*)); 
   //  const char* path = wrenGetSlotString(vm, 1); 
   //  *file = fopen(path, "r+"); 
}

/**
 *  io/file::Finalize
 * 
 */
void io_file_Finalize(void* data) 
{ 
   //  io_stream_close_file((FILE**) data); 
}
