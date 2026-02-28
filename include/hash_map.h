#ifndef HASH_HASH_MAP_H
#define HASH_HASH_MAP_H

#include "error.h"
#include <stddef.h>

#ifndef GENERIC_ARGMENT_1
    #define GENERIC_ARGMENT_1 char
    #define GENERIC_ARGMENT_2 short
    #define GENERIC_ARGMENT_4 long
    #define GENERIC_ARGMENT_8 size_t
#endif

#define DECLARE_HASH_MAP(TYPE, STRUCT_NAME) \
struct STRUCT_NAME ## Entry \
{ \
    size_t hash; \
    char *key; \
    TYPE p; \
}; \
struct STRUCT_NAME \
{ \
    struct STRUCT_NAME ## Entry *p; \
    size_t size; \
    size_t deleted; \
    size_t capacity; \
};

#define DECLARE_HASH_MAP_FINALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## finalize(struct STRUCT_NAME *map);
#define DECLARE_HASH_MAP_READ(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## read(const struct STRUCT_NAME *map, const char *key, TYPE *data); /* Find existing key, return if exists */
#define DECLARE_HASH_MAP_ERASE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## erase(struct STRUCT_NAME *map, const char *key); /* Erase existing key, return if existed */
#define DECLARE_HASH_MAP_WRITE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
ERROR_TYPE FUNCTION_NAME ## write(struct STRUCT_NAME *map, const char *key, TYPE data) NODISCARD; /* Insert key, overwrite existing */

#endif
