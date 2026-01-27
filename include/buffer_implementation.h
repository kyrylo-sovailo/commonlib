#ifndef BUFFER_IMPLEMENTATION_H
#define BUFFER_IMPLEMENTATION_H

#include "buffer.h"

#define IMPLEMENT_BUFFER_FINALIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
void FRIENDLY_LOWER ## _buffer_finalize(struct FRIENDLY_UPPER ## Buffer *buffer) \
{ \
    generic_buffer_finalize(buffer); \
}
#define IMPLEMENT_BUFFER_RESIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_resize(struct FRIENDLY_UPPER ## Buffer *buffer, size_t size) \
{ \
    switch (sizeof(*buffer->p)) \
    { \
    case 1: return generic_buffer_resize_1(buffer, size); \
    case 2: return generic_buffer_resize_2(buffer, size); \
    case 4: return generic_buffer_resize_4(buffer, size); \
    case 8: return generic_buffer_resize_8(buffer, size); \
    default: return generic_buffer_resize_n(sizeof(*buffer->p), buffer, size); \
    } \
}
#define IMPLEMENT_BUFFER_APPEND(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_append(struct FRIENDLY_UPPER ## Buffer *buffer, const TYPE *data, size_t size) \
{ \
    switch (sizeof(*buffer->p)) \
    { \
    case 1: return generic_buffer_append_1(buffer, data, size); \
    case 2: return generic_buffer_append_2(buffer, data, size); \
    case 4: return generic_buffer_append_4(buffer, data, size); \
    case 8: return generic_buffer_append_8(buffer, data, size); \
    default: return generic_buffer_append_n(sizeof(*buffer->p), buffer, data, size); \
    } \
}
#define IMPLEMENT_BUFFER_PUSH(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER, SIZE) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_push(struct FRIENDLY_UPPER ## Buffer *buffer, TYPE data) \
{ \
    ERROR_TYPE check[(sizeof(*buffer->p) == SIZE && sizeof(data) == SIZE) ? 1 : -1]; \
    check[0] = generic_buffer_push_ ## SIZE(buffer, (GENERIC_ARGMENT_ ## SIZE)data); \
    return check[0]; \
}

void generic_buffer_finalize(void *buffer);

ERROR_TYPE generic_buffer_resize_1(void *buffer, size_t size);
ERROR_TYPE generic_buffer_resize_2(void *buffer, size_t size);
ERROR_TYPE generic_buffer_resize_4(void *buffer, size_t size);
ERROR_TYPE generic_buffer_resize_8(void *buffer, size_t size);
ERROR_TYPE generic_buffer_resize_n(void *buffer, size_t size, size_t element_sizeof);

ERROR_TYPE generic_buffer_reserve_1(void *buffer, size_t size);
ERROR_TYPE generic_buffer_reserve_2(void *buffer, size_t size);
ERROR_TYPE generic_buffer_reserve_4(void *buffer, size_t size);
ERROR_TYPE generic_buffer_reserve_8(void *buffer, size_t size);
ERROR_TYPE generic_buffer_reserve_n(void *buffer, size_t size, size_t element_sizeof);

ERROR_TYPE generic_buffer_append_1(void *buffer, const void *data, size_t size);
ERROR_TYPE generic_buffer_append_2(void *buffer, const void *data, size_t size);
ERROR_TYPE generic_buffer_append_4(void *buffer, const void *data, size_t size);
ERROR_TYPE generic_buffer_append_8(void *buffer, const void *data, size_t size);
ERROR_TYPE generic_buffer_append_n(void *buffer, const void *data, size_t size, size_t element_sizeof);

ERROR_TYPE generic_buffer_push_1(void *buffer, GENERIC_ARGMENT_1 data);
ERROR_TYPE generic_buffer_push_2(void *buffer, GENERIC_ARGMENT_2 data);
ERROR_TYPE generic_buffer_push_4(void *buffer, GENERIC_ARGMENT_4 data);
ERROR_TYPE generic_buffer_push_8(void *buffer, GENERIC_ARGMENT_8 data);

#endif
