#include "../include/buffer_implementation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DECLARE_BUFFER(GENERIC_ARGMENT_1, Generic1Byte, generic_byte)
DECLARE_BUFFER(GENERIC_ARGMENT_2, Generic2Byte, generic_word)
DECLARE_BUFFER(GENERIC_ARGMENT_4, Generic4Byte, generic_dword)
DECLARE_BUFFER(GENERIC_ARGMENT_8, Generic8Byte, generic_qword)

#define IMPLEMENT_GENERIC_BUFFER_RESIZE(FRIENDLY_UPPER, SIZE_EXPRESSION) \
{ \
    struct FRIENDLY_UPPER ## Buffer* cast = (struct FRIENDLY_UPPER ## Buffer*)buffer; \
    if (size > cast->capacity) \
    { \
        void *new_p; \
        size_t new_capacity = (cast->capacity == 0) ? 1 : cast->capacity; \
        while (size > new_capacity) new_capacity <<= 1; \
        new_p = realloc(cast->p, new_capacity * SIZE_EXPRESSION); \
        CRET(new_p != NULL); \
        cast->capacity = new_capacity; \
        cast->p = new_p; \
    } \
    cast->size = size; \
    ERROR_RETURN_OK(); \
}

#define IMPLEMENT_GENERIC_BUFFER_RESERVE(FRIENDLY_UPPER, SIZE_EXPRESSION) \
{ \
    struct FRIENDLY_UPPER ## Buffer* cast = (struct FRIENDLY_UPPER ## Buffer*)buffer; \
    if (size > cast->capacity) \
    { \
        void *new_p; \
        size_t new_capacity = (cast->capacity == 0) ? 1 : cast->capacity; \
        while (size > new_capacity) new_capacity <<= 1; \
        new_p = realloc(cast->p, new_capacity * SIZE_EXPRESSION); \
        CRET(new_p != NULL); \
        cast->capacity = new_capacity; \
        cast->p = new_p; \
    } \
    cast->size = size; \
    ERROR_RETURN_OK(); \
}

#define IMPLEMENT_GENERIC_BUFFER_APPEND(FRIENDLY_UPPER, SIZE_EXPRESSION, OLD_SIZE_POINTER_EXPRESSION) \
{ \
    struct FRIENDLY_UPPER ## Buffer* cast = (struct FRIENDLY_UPPER ## Buffer*)buffer; \
    if (cast->size + size > cast->capacity) \
    { \
        void *new_p; \
        size_t new_capacity = (cast->capacity == 0) ? 1 : cast->capacity; \
        while (cast->size + size > new_capacity) new_capacity <<= 1; \
        new_p = realloc(cast->p, new_capacity * SIZE_EXPRESSION); \
        CRET(new_p != NULL); \
        cast->capacity = new_capacity; \
        cast->p = new_p; \
    } \
    memcpy(OLD_SIZE_POINTER_EXPRESSION, data, size * SIZE_EXPRESSION); \
    cast->size += size; \
    ERROR_RETURN_OK(); \
}

#define IMPLEMENT_GENERIC_BUFFER_PUSH(FRIENDLY_UPPER, SIZE_EXPRESSION) \
{ \
    struct FRIENDLY_UPPER ## Buffer* cast = (struct FRIENDLY_UPPER ## Buffer*)buffer; \
    if (cast->size + 1 > cast->capacity) \
    { \
        const size_t new_capacity = (cast->capacity == 0) ? 1 : (cast->capacity << 1); \
        void *new_p = realloc(cast->p, new_capacity * SIZE_EXPRESSION); \
        CRET(new_p != NULL); \
        cast->capacity = new_capacity; \
        cast->p = new_p; \
    } \
    cast->p[cast->size] = data; \
    cast->size += 1; \
    ERROR_RETURN_OK(); \
}

void generic_buffer_finalize(void *buffer)
{
    struct Generic1ByteBuffer* cast = (struct Generic1ByteBuffer*)buffer;
    if (cast->p != NULL) free(cast->p);
    memset(cast, 0, sizeof(*cast));
}

ERROR_TYPE generic_buffer_resize_1(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESIZE(Generic1Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_resize_2(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESIZE(Generic2Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_resize_4(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESIZE(Generic4Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_resize_8(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESIZE(Generic8Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_resize_n(void *buffer, size_t size, size_t element_sizeof)
IMPLEMENT_GENERIC_BUFFER_RESIZE(Generic1Byte, element_sizeof)

ERROR_TYPE generic_buffer_reserve_1(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESERVE(Generic1Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_reserve_2(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESERVE(Generic2Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_reserve_4(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESERVE(Generic4Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_reserve_8(void *buffer, size_t size)
IMPLEMENT_GENERIC_BUFFER_RESERVE(Generic8Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_reserve_n(void *buffer, size_t size, size_t element_sizeof)
IMPLEMENT_GENERIC_BUFFER_RESERVE(Generic1Byte, element_sizeof)

ERROR_TYPE generic_buffer_append_1(void *buffer, const void *data, size_t size)
IMPLEMENT_GENERIC_BUFFER_APPEND(Generic1Byte, sizeof(*cast->p), cast->p + cast->size)
ERROR_TYPE generic_buffer_append_2(void *buffer, const void *data, size_t size)
IMPLEMENT_GENERIC_BUFFER_APPEND(Generic2Byte, sizeof(*cast->p), cast->p + cast->size)
ERROR_TYPE generic_buffer_append_4(void *buffer, const void *data, size_t size)
IMPLEMENT_GENERIC_BUFFER_APPEND(Generic4Byte, sizeof(*cast->p), cast->p + cast->size)
ERROR_TYPE generic_buffer_append_8(void *buffer, const void *data, size_t size)
IMPLEMENT_GENERIC_BUFFER_APPEND(Generic8Byte, sizeof(*cast->p), cast->p + cast->size)
ERROR_TYPE generic_buffer_append_n(void *buffer, const void *data, size_t size, size_t element_sizeof)
IMPLEMENT_GENERIC_BUFFER_APPEND(Generic1Byte, element_sizeof, cast->p + cast->size * element_sizeof)

ERROR_TYPE generic_buffer_push_1(void *buffer, GENERIC_ARGMENT_1 data)
IMPLEMENT_GENERIC_BUFFER_PUSH(Generic1Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_push_2(void *buffer, GENERIC_ARGMENT_2 data)
IMPLEMENT_GENERIC_BUFFER_PUSH(Generic2Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_push_4(void *buffer, GENERIC_ARGMENT_4 data)
IMPLEMENT_GENERIC_BUFFER_PUSH(Generic4Byte, sizeof(*cast->p))
ERROR_TYPE generic_buffer_push_8(void *buffer, GENERIC_ARGMENT_8 data)
IMPLEMENT_GENERIC_BUFFER_PUSH(Generic8Byte, sizeof(*cast->p))
