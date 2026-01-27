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

#define DECLARE_HASH_MAP(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
struct FRIENDLY_UPPER ## HashMapEntry \
{ \
    size_t hash; \
    char *key; \
    TYPE p; \
}; \
struct FRIENDLY_UPPER ## HashMap \
{ \
    struct FRIENDLY_UPPER ## HashMapEntry *p; \
    size_t size; \
    size_t deleted; \
    size_t capacity; \
};

#define DECLARE_HASH_MAP_FINALIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
void FRIENDLY_LOWER ## _hmap_finalize(struct FRIENDLY_UPPER ## HashMap *map);
#define DECLARE_HASH_MAP_READ(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
bool FRIENDLY_LOWER ## _hmap_read(const struct FRIENDLY_UPPER ## HashMap *map, const char *key, TYPE *data); /* Find existing key, return if exists */
#define DECLARE_HASH_MAP_ERASE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
bool FRIENDLY_LOWER ## _hmap_erase(struct FRIENDLY_UPPER ## HashMap *map, const char *key); /* Erase existing key, return if existed */
#define DECLARE_HASH_MAP_WRITE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
ERROR_TYPE FRIENDLY_LOWER ## _hmap_write(struct FRIENDLY_UPPER ## HashMap *map, const char *key, TYPE data) NODISCARD; /* Insert key, overwrite existing */

#endif
