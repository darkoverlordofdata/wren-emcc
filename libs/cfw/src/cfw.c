#include "cfw.h"
struct CFWArray {
	CFWObject obj;
	void **data;
	size_t size;
};

/**
 * CoreFW wrappers
 */

overloadable void Clear(CFWArray* this)
{

	for (int i = 0; i < this->size; i++)
		cfw_unref(this->data[i]);

	if (this->data != NULL)
		free(this->data);
    this->size = 0;
}

overloadable void* New(CFWString* this)
{
    return cfw_new(cfw_string, NULL);
}
overloadable void* New(CFWString* this, char* value)
{
    return cfw_new(cfw_string, value);    
}

overloadable void* Get(CFWArray* this, int i)
{
    return cfw_array_get(this, i);
}

overloadable void* Get(CFWMap* this, char* key)
{
    return cfw_map_get(this, key);
}

overloadable void Add(CFWArray* this, void* item)
{
    cfw_array_push(this, item);
}

overloadable bool Remove(CFWMap* this, char* key)
{
    return cfw_map_set(this, key, NULL);
}

overloadable void Put(CFWMap* this, char* key, void* object)
{
    cfw_map_set(this, key, object);
}

overloadable void Put(CFWArray* this, int index, void* object)
{
    cfw_array_set(this, index, object);
}

// overloadable void ForEach(CFWMap* this, void(*func)(void* item))
overloadable void ForEach(CFWMap* this, void(*func)(void* key, void* item))
{
   cfw_map_iter_t iter;

    cfw_map_iter(this, &iter);
    while (iter.key != NULL) {
        func(iter.key, iter.obj);
        cfw_map_iter_next(&iter);
    }
}
overloadable void ForEach(CFWMap* this, void(^func)(void* key, void* item))
{
    cfw_map_iter_t iter;

    cfw_map_iter(this, &iter);
    while (iter.key != NULL) {
        func(iter.key, iter.obj);
        cfw_map_iter_next(&iter);
    }
}

overloadable char* cstr(CFWString* this)
{
    return cfw_string_c(this);
}

overloadable char* ToString(CFWString* this)
{
    return cfw_string_c(this);
}

overloadable int Length(CFWArray* this)
{
    return cfw_array_size(this);
}

overloadable int Length(CFWString* this)
{
    return cfw_string_length(this);
}

/**
 * join strings
 * 
 * @param count of strings
 * @param ... list of char*'s
 * @returns all strings concantenated together.
 */
char* STR_JOIN(int count, ...)
{
    
    int size = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);  

    /**
     * Caclulate length of the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args1, char*);
        size += strlen(str);
    }
    va_end(args1);
    char* result = (char*)calloc((size+1),  sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args2, char*);
        strcat(result, str);
    }
    va_end(args2);
    return result;
}
