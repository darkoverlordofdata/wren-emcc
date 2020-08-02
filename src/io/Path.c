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
#include "io/Path.h"

/**
 *  io.path.Allocate
 */
void io_path_Allocate(WrenVM* vm)
{
    // printf("io_path_Allocate\n");
    Path** path = (Path**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Path*));
    const char* value = wrenGetSlotString(vm, 1);
    // printf("io_path_Allocate - value: %s\n", value);
    *path = pathNew(value);
}

/**
 *  io.path.Finalize
 * 
 */
void io_path_Finalize(void* data)
{
    Path** path = (Path**)data;
    pathFree(*path);
}

void io_path_Absolute(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_ABSOLUTE);
}
void io_path_Relative(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_RELATIVE);
}
void io_path_Simple(WrenVM* vm)
{
    wrenSetSlotDouble(vm, 0, PATH_TYPE_SIMPLE);
}

void io_path_Cwd(WrenVM* vm)
{
    char cwd[PATH_MAX];

    if (GetCwd(cwd, sizeof(cwd)) == NULL) {
        wrenSetSlotString(vm, 0, "No CWD!");
        wrenAbortFiber(vm, 0);
        return;
    }
    wrenSetSlotString(vm, 0, cwd);
}
/**
 *  io.path.type
 * 
 *  Categorizes what form a path is.
 */
void io_path_Type(WrenVM* vm)
{
    const char* path = wrenGetSlotString(vm, 1);
    wrenSetSlotDouble(vm, 0, pathType(path));
}
/**
 *  io.path.DirName
 * 
 *  Strips off the last component of the path name.
 */
void io_path_DirName(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathDirName(*path);
}

/**
 *  io.path.RemoveExtension
 * 
 *  Strips off the file extension from the last component of the path.
 */
void io_path_RemoveExtension(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathRemoveExtension(*path);
}

/**
 *  io.path.Join
 * 
 *  Appends [string] to [path].
 */
void io_path_Join(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1);
    pathJoin(*path, value);
}

/**
 *  io.path.AppendChar
 * 
 *  Appends [c] to the path, growing the buffer if needed.
 */
void io_path_AppendChar(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1);
    pathAppendChar(*path, value[0]);
}

/**
 *  io.path.AppendString
 * 
 *  Appends [string] to the path, growing the buffer if needed.
 */
void io_path_AppemdString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1);
    pathAppendString(*path, value);
}

/**
 *  io.path.Normalize
 * 
 *  Simplifies the path string as much as possible.
 *
 *  Applies and removes any "." or ".." components, collapses redundant "/"
 *  characters, and normalizes all path separators to "/".
 */
void io_path_Normalize(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathNormalize(*path);
}

/**
 *  io.path.ToString
 * 
 *  Allocates a new string exactly the right length and copies this path to it.
 */
void io_path_ToString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    char* value = pathToString(*path);
    wrenSetSlotString(vm, 0, value);
}
