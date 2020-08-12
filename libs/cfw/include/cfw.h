#pragma once
#include <corefw/corefw.h>

/**
 *  MACRO var
 *      type inferencing declare
 */
#define var __auto_type

/**
 *  MACRO overloadable
 *      enable multi-methods 
 */
#define overloadable __attribute__((overloadable))

/**
 *  MACRO Min
 *      cache results of calculation in pocket scope 
 */
#define Min(a, b)            \
    ({                       \
        __auto_type _a = a;  \
        __auto_type _b = b;  \
        (_a < _b) ? _a : _b; \
    })

/**
 *  MACRO Max
 *      cache results of calculation in pocket scope 
 */
#define Max(a, b)            \
    ({                       \
        __auto_type _a = a;  \
        __auto_type _b = b;  \
        (_a > _b) ? _a : _b; \
    })

/**
 *  MACRO NARG
 *      Count the number of arguments
 */
#define PP_NARG(...)                                                    \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                                                   \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                                                       \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,                       \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,                       \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,                       \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,                       \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,                       \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,                       \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N()                                                     \
         63,62,61,60,                                                   \
         59,58,57,56,55,54,53,52,51,50,                                 \
         49,48,47,46,45,44,43,42,41,40,                                 \
         39,38,37,36,35,34,33,32,31,30,                                 \
         29,28,27,26,25,24,23,22,21,20,                                 \
         19,18,17,16,15,14,13,12,11,10,                                 \
         9,8,7,6,5,4,3,2,1,0

/**
 *  MACRO join
 *      String.join(..)
 */
#define join(...) strnjoin(PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define CFWArrayClass cfw_array
#define CFWBoolClass cfw_bool
#define CFWDoubleClass cfw_double
#define CFWFileClass cfw_file
#define CFWIntClass cfw_int
#define CFWMapClass cfw_map
#define CFWRangeClass cfw_range
#define CFWStreamClass cfw_stream
#define CFWStringClass cfw_string

/**
 *  MACRO new
 *      Create a new CoreFW object from the current memory pool
 */
#define new(T, args...) (T*)New((T*)cfw_create((CFWClass*)T##Class), ## args)

    // var fred = (CFWString*)cfw_create(CFWStringClass, "Fred");

// #define new_(T, args...)(T*)cfw_create((CFWClass*)T##Class, ## args)
#define new_(T, args...)(T*)cfw_create((CFWClass*)T##Class, ## args)
/**
 * MACRO class
 *      generate typeinfo boilerplate for corefw
 */
#define class(T)                        \
    typedef struct T T;                 \
    static bool ctor(void*, va_list);   \
    static void dtor(void*);            \
    static bool equal(void*, void*);    \
    static uint32_t hash(void*);        \
    static void* copy(void*);           \
    const static CFWClass class = {     \
        .name = #T,                     \
        .size = sizeof(T),              \
        .ctor = ctor,                   \
        .dtor = dtor,                   \
        .equal = equal,                 \
        .hash = hash,                   \
        .copy = copy                    \
    };                                  \
    const CFWClass* T##Class = &class


#include "cfwfs.h"
#include "bitvector.h"
#include "random.h"
#include "uuid.h"

extern overloadable void Clear(CFWArray* this);
extern overloadable void* Get(CFWArray* this, int i);
extern overloadable void* Get(CFWMap* this, char* key);
extern overloadable void Add(CFWArray* this, void* item);
extern overloadable bool Remove(CFWArray* this, int i);
extern overloadable bool Remove(CFWMap* this, char* key);
extern overloadable void Put(CFWMap* this, char* key, void* object);
extern overloadable void Put(CFWArray* this, int index, void* object);
extern overloadable void ForEach(CFWMap* this, void(^func)(void* key, void* item));
extern overloadable void ForEach(CFWMap* this, void(*func)(void* key, void* item));
extern overloadable int Length(CFWArray* this);
extern overloadable int Length(CFWString* this);
extern overloadable char* cstr(CFWString* this);
extern overloadable char* ToString(CFWString* this);

extern overloadable void* New(CFWString* this);
extern overloadable void* New(CFWString* this, const char* value);
extern overloadable void* New(CFWMap* this);
extern overloadable void* New(CFWArray* this);
extern overloadable void* New(CFWDouble* this, double value);
extern overloadable void* New(CFWInt* this, int value);
extern overloadable void* New(CFWFile* this, char* path, char* mode);
extern overloadable void* New(CFWStream* this, char* path, char* mode);
extern overloadable void* New(CFWBool* this, bool value);

static inline struct CFWObject* asObject(void* obj) { return obj; }
char* strnjoin(int count, ...);

