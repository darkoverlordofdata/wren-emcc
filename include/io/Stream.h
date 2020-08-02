#pragma once
#include <stdio.h>
#include <string.h>
#include <wren.h>

/**
 *  private
 *  io/file::close_file
 */
void io_stream_close_file(FILE** file);
void io_stream_Allocate(WrenVM* vm);
void io_stream_Finalize(void* data);
void io_stream_Write(WrenVM* vm);
void io_stream_Read(WrenVM* vm);
void io_stream_Close(WrenVM* vm);
