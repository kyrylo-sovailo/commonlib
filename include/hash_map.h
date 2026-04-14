#ifndef COMMONLIB_HASH_MAP_H
#define COMMONLIB_HASH_MAP_H

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
    cchar_t *key; \
    TYPE p; \
}; \
struct STRUCT_NAME \
{ \
    struct STRUCT_NAME ## Entry *p; \
    size_t size; \
    size_t deleted; \
    size_t capacity; \
};

#define DECLARE_HASH_MAP_INITIALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## initialize(struct STRUCT_NAME *map);
#define DECLARE_HASH_MAP_FINALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## finalize(struct STRUCT_NAME *map);
#define DECLARE_HASH_MAP_VALID(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## valid(struct STRUCT_NAME ## Entry *entry);
#define DECLARE_HASH_MAP_ACCESS(TYPE, STRUCT_NAME, FUNCTION_NAME) \
ERROR_TYPE FUNCTION_NAME ## access(struct STRUCT_NAME *map, const cchar_t *key, struct STRUCT_NAME ## Entry **entry, bool create) NODISCARD; /* Primary function, others are wrappers */
#define DECLARE_HASH_MAP_DELETE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## delete(struct STRUCT_NAME *map, struct STRUCT_NAME ## Entry *entry); /* Secondary function, others are wrappers */

#endif
