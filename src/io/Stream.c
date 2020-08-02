#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "io/Stream.h"

/**
 *  private
 *  io/file::close_file
 */
void io_stream_close_file(FILE** file) 
{ 
    if (*file == NULL) return;
    fclose(*file); 
    *file = NULL; 
}


/**
 *  io/file::Allocate
 */
void io_stream_Allocate(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenSetSlotNewForeign(vm, 0, 0, sizeof(FILE*)); 
    const char* path = wrenGetSlotString(vm, 1); 
    *file = fopen(path, "r+"); 
}

/**
 *  io/file::Finalize
 * 
 */
void io_stream_Finalize(void* data) 
{ 
    io_stream_close_file((FILE**) data); 
}


/**
 *  io/file::Write
 * 
 */
void io_stream_Write(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenGetSlotForeign(vm, 0);

    // Make sure the file is still open.
    if (*file == NULL) 
    { 
        wrenSetSlotString(vm, 0, "Cannot write to a closed file."); 
        wrenAbortFiber(vm, 0); 
        return; 
    }

    const char* text = wrenGetSlotString(vm, 1); 
    fwrite(text, sizeof(char), strlen(text), *file); 
}

void io_stream_Read(WrenVM* vm)
{
    FILE** file = (FILE**)wrenGetSlotForeign(vm, 0);

    // Make sure the file is still open.
    if (*file == NULL) 
    { 
        wrenSetSlotString(vm, 0, "Cannot read from a closed file."); 
        wrenAbortFiber(vm, 0); 
        return; 
    }
    fseek(*file, 0, SEEK_END);
    size_t fileSize = ftell(*file);
    rewind(*file);
    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        wrenSetSlotString(vm, 0, "Cannot allocate memory to read from file."); 
        wrenAbortFiber(vm, 0); 
        return; 
    }
    size_t bytesRead = fread(buffer, 1, fileSize, *file);
    if (bytesRead < fileSize)
    {
        wrenSetSlotString(vm, 0, "Cannot read from file."); 
        wrenAbortFiber(vm, 0); 
        return; 
    }
    buffer[bytesRead] = '\0';
    wrenSetSlotBytes(vm, 0, buffer, bytesRead);
}
/**
 *  io/file::Close
 * 
 */
void io_stream_Close(WrenVM* vm) 
{ 
    FILE** file = (FILE**)wrenGetSlotForeign(vm, 0); 
    io_stream_close_file(file); 
}
