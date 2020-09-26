#include <stdio.h>
#include <string.h>
#include <wren.h>
#include <limits.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#include "wren/path.h"
#include "io/Path.h"
/**
 * Wren bindings for Path object
 */
/**
 *  io_path_Allocate
 */
void io_path_Allocate(WrenVM* vm)
{
    Path** path = (Path**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Path*));
    const char* value = wrenGetSlotString(vm, 1);
    *path = pathNew(value);
}

/**
 *  io_path_Finalize
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
#ifdef _WIN32
    char cwd[MAX_PATH];
    if (_getcwd(cwd, sizeof(cwd)) == NULL) 
#else
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
#endif
    {
        wrenSetSlotString(vm, 0, "No CWD!");
        wrenAbortFiber(vm, 0);
        return;
    }
    wrenSetSlotString(vm, 0, cwd);
}
/**
 *  io_path_type
 * 
 *  Categorizes what form a path is.
 */
void io_path_Type(WrenVM* vm)
{
    const char* path = wrenGetSlotString(vm, 1);
    wrenSetSlotDouble(vm, 0, pathType(path));
}
/**
 *  io_path_DirName
 * 
 *  Strips off the last component of the path name.
 */
void io_path_DirName(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathDirName(*path);
}

/**
 *  io_path_RemoveExtension
 * 
 *  Strips off the file extension from the last component of the path.
 */
void io_path_RemoveExtension(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    pathRemoveExtension(*path);
}

/**
 *  io_path_Join
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
 *  io_path_AppendChar
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
 *  io_path_AppendString
 * 
 *  Appends [string] to the path, growing the buffer if needed.
 */
void io_path_AppendString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    const char* value = wrenGetSlotString(vm, 1);
    pathAppendString(*path, value);
}

/**
 *  io_path_Normalize
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
 *  io_path_ToString
 * 
 *  Allocates a new string exactly the right length and copies this path to it.
 */
void io_path_ToString(WrenVM* vm)
{
    Path** path = (Path**)wrenGetSlotForeign(vm, 0);
    char* value = pathToString(*path);
    wrenSetSlotString(vm, 0, value);
    free(value); // wren created it's own copy
}
