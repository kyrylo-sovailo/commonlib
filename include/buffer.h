#ifndef BUFFER_H
#define BUFFER_H

#include "error.h"

#include <stddef.h>

#ifndef GENERIC_ARGMENT_1
    #define GENERIC_ARGMENT_1 char
    #define GENERIC_ARGMENT_2 short
    #define GENERIC_ARGMENT_4 signed
    #define GENERIC_ARGMENT_8 long
#endif

#define DECLARE_BUFFER(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
struct FRIENDLY_UPPER ## Buffer \
{ \
    TYPE *p; \
    size_t size; \
    size_t capacity; \
};

#define DECLARE_BUFFER_FINALIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
void FRIENDLY_LOWER ## _buffer_finalize(struct FRIENDLY_UPPER ## Buffer *buffer);
#define DECLARE_BUFFER_RESIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_resize(struct FRIENDLY_UPPER ## Buffer *buffer, size_t size) NODISCARD;
#define DECLARE_BUFFER_RESERVE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_reserve(struct FRIENDLY_UPPER ## Buffer *buffer, size_t capacity) NODISCARD;
#define DECLARE_BUFFER_APPEND(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_append(struct FRIENDLY_UPPER ## Buffer *buffer, const TYPE *data, size_t size) NODISCARD;
#define DECLARE_BUFFER_PUSH(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _buffer_push(struct FRIENDLY_UPPER ## Buffer *buffer, TYPE data) NODISCARD;

#endif
