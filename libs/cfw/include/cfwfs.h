#pragma once
#include <corefw/object.h>
#include <corefw/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CFWFS {
    CFWString* (*getPath)(const char* path);
    char* const (*getRoot)();
    CFWString* (*getPathRelativeRoot)(const char* path);
    CFWString* (*getPathRelativeBinary)(const char* path);
    CFWString* (*readTextFile)(char* path);
};

extern struct CFWFS CFWFS;