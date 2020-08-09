/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c) 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#include "bitvector.h"
#include "bitvector-private.h"
#include "cfw.h"
#include "stdlib.h"

class(CFWBitVector);
static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

/*
 * CFWBitVectors are packed into arrays of "words."  Currently a word
 * consists of 32 bits, requiring 5 address bits.
 */
const int ADDRESS_BITS_PER_WORD = 5;
const int64_t BITS_PER_WORD = 1 << ADDRESS_BITS_PER_WORD; // 32
const int64_t WORD_MASK = 0xffffffff;
/**
 * @see http://stackoverflow.com/questions/6506356/java-implementation-of-long-numberoftrailingzeros
 */
unsigned int numberOfTrailingZeros(unsigned int i)
{
    if (i == 0)
        return 32;
    unsigned int x = i;
    unsigned int y;
    unsigned int n = 31;
    y = x << 16;
    if (y != 0) {
        n -= 16;
        x = y;
    }
    y = x << 8;
    if (y != 0) {
        n -= 8;
        x = y;
    }
    y = x << 4;
    if (y != 0) {
        n -= 4;
        x = y;
    }
    y = x << 2;
    if (y != 0) {
        n -= 2;
        x = y;
    }
    return (n - ((x << 1) >> 31));
}

/**
 * Constructor
 * create a new CFWBitVector
 * 
 * @param value of bool
 * 
 */
overloadable void* New(CFWBitVector* this, int nbits)
{
    this->length = 0;
    if (nbits > 0) {
        int size = (((nbits - 1) >> ADDRESS_BITS_PER_WORD) + 1);
        this->words = calloc(size, sizeof(unsigned int));
        for (int i = 0; i < size; i++)
            this->words[i] = 0;
        this->length = size;
    }
    return this;
}

overloadable void* New(CFWBitVector* this)
{
    return New(this, 16);
}

overloadable int NextSetBit(CFWBitVector* this, int fromIndex)
{
    int u = fromIndex >> ADDRESS_BITS_PER_WORD;
    int wordsInUse = this->length;

    int word = this->words[u] & (WORD_MASK << fromIndex);
    while (true) {
        if (word != 0)
            return (int)((u * BITS_PER_WORD) + numberOfTrailingZeros(word));
        if (++u == wordsInUse)
            return -1;
        word = this->words[u];
    }
}

overloadable bool Intersects(CFWBitVector* this, CFWBitVector* set)
{
    int wordsInUse = this->length;

    for (int i = Min(wordsInUse, set->length) - 1; i >= 0; i--)
        if ((this->words[i] & set->words[i]) != 0)
            return true;
    return false;
}

overloadable bool IsEmpty(CFWBitVector* this)
{
    return this->length == 0;
}

overloadable void Set(CFWBitVector* this, int bitIndex, bool value)
{
    int wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    int wordsInUse = this->length;
    int wordsRequired = wordIndex + 1;

    if (wordIndex >= this->length) {
        this->words = realloc(this->words, sizeof(unsigned int) * (wordIndex + 1));
        // this = realloc(this, sizeof(CFWObject) + sizeof(int) + sizeof(unsigned int) * wordIndex + 1);
    }
    if (wordsInUse < wordsRequired) {

        int mm = Max(2 * wordsInUse, wordsRequired);
        // words.resize(int.max(2 * wordsInUse, wordsRequired));
        // this = realloc(this, sizeof(CFWObject) + sizeof(int) + sizeof(unsigned int) * Max(2 * wordsInUse, wordsRequired));
        this->words = realloc(this->words, sizeof(unsigned int) * mm);
        for (int i = wordsInUse, l = this->length; i < l; i++) {
            this->words[i] = 0;
        }
    }

    if (value) {
        this->words[wordIndex] |= (1 << bitIndex);
    } else {
        this->words[wordIndex] &= ~(1 << bitIndex);
    }
}

overloadable bool Get(CFWBitVector* this, int bitIndex)
{
    int wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    int wordsInUse = this->length;

    return (wordIndex < wordsInUse) && ((this->words[wordIndex] & (1 << bitIndex)) != 0);
}

overloadable void overloadable Clear(CFWBitVector* this, int bitIndex)
{
    if (bitIndex == -1) {
        int wordsInUse = this->length;
        while (wordsInUse > 0) {
            this->words[--wordsInUse] = 0;
        }
        return;
    }

    int wordIndex = bitIndex >> ADDRESS_BITS_PER_WORD;
    if (this->length <= wordIndex) {
        this->words = realloc(this->words, sizeof(unsigned int) * wordIndex + 1);
        // this = realloc(this, sizeof(CFWObject) + sizeof(int) + sizeof(unsigned int) * wordIndex + 1);
    }
    this->words[wordIndex] &= ~(1 << bitIndex);
}

overloadable void overloadable Clear(CFWBitVector* this)
{
    Clear(this, -1);
}

/**
 * Returns the string value of this CFWBitVector
 */
overloadable char* ToString(CFWBitVector* this)
{
    return "CFWBitVector";
    //     string[] s = new string[words.length];
    //     for (var i=0; i<words.length; i++)
    //     {
    //         s[i] = "0x%08x".printf(words[i]);
    //     }
    //     return string.joinv("|", s);
    // }
}
