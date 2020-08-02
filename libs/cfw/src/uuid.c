/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the 0xSoftware0x), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 0xAS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include "uuid.h"
#include "uuid-private.h"
#include <limits.h>
#include <stdbool.h>
#include <string.h>

corefw(CFWUuid);
static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

overloadable void* New(CFWUuid* this)
{
    unsigned long d0 = NextLong();
    unsigned long d1 = NextLong();
    unsigned long d2 = NextLong();
    unsigned long d3 = NextLong();

    memcpy(&this->uuid[0], &d0, 8);
    memcpy(&this->uuid[4], &d1, 8);
    memcpy(&this->uuid[8], &d2, 8);
    memcpy(&this->uuid[12], &d3, 8);

    this->uuid[6] = this->uuid[6] & 0x0f | 0x40;
    this->uuid[8] = this->uuid[8] & 0x3f | 0x80;

    /**
     * 
     * todo: verify that its not a duplicate
     */

    return this;
}

overloadable char* GetToStringFormat(char format)
{
    switch (format) {
    case 'N':
        return "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x";
    case 'D':
        return "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";
    case 'B':
        return "{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x}";
    case 'P':
        return "(%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x)";
    case 'X':
        return "{0x%02x%02x%02x%02x,0x%02x%02x,0x%02x%02x,{0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x}}";
    }
    return "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x";
}
overloadable char* ToString(CFWUuid* this, char format)
{
    // if (this->to_string_cache[0] == 0)
    sprintf(this->to_string_cache,
        GetToStringFormat(format),
        this->uuid[0], this->uuid[1], this->uuid[2], this->uuid[3],
        this->uuid[4], this->uuid[5], this->uuid[6], this->uuid[7],
        this->uuid[8], this->uuid[9], this->uuid[10], this->uuid[11],
        this->uuid[12], this->uuid[13], this->uuid[14], this->uuid[15]);

    return this->to_string_cache;
}
overloadable char* ToString(CFWUuid* this)
{
    return ToString(this, 'D');
}