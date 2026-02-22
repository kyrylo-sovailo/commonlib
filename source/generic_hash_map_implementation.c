#include "../include/hash_map_implementation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GenericHashKey
{
    size_t hash;
    char *key;
};

DECLARE_HASH_MAP(GENERIC_ARGMENT_1, Generic1Byte, generic_byte)
DECLARE_HASH_MAP(GENERIC_ARGMENT_2, Generic2Byte, generic_word)
DECLARE_HASH_MAP(GENERIC_ARGMENT_4, Generic4Byte, generic_dword)
DECLARE_HASH_MAP(GENERIC_ARGMENT_8, Generic8Byte, generic_qword)

#define IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(FRIENDLY_UPPER) \
{ \
    struct FRIENDLY_UPPER ## HashMap *cast = (struct FRIENDLY_UPPER ## HashMap*)map; \
    struct FRIENDLY_UPPER ## HashMapEntry *entry; \
    for (entry = cast->p; entry != cast->p + cast->capacity; entry++) \
    { \
        if (entry->key != (void*)0 && entry->key != (void*)-1) free(entry->key); \
    } \
    if (cast->p != NULL) free(cast->p); \
    memset(cast, 0, sizeof(*cast)); \
}

#define IMPLEMENT_GENERIC_HASH_MAP_FIND(FRIENDLY_UPPER) \
{ \
    const struct FRIENDLY_UPPER ## HashMap *cast = (const struct FRIENDLY_UPPER ## HashMap*)map; \
    const size_t hash = fnv1a(key); \
    const size_t mask = cast->capacity - 1; \
    size_t position = hash & mask; \
    if (cast->size == 0) return false; \
    while (true) \
    { \
        if (cast->p[position].key == (void*)0) /* Ivalid */ \
        { \
            return false; \
        } \
        else if (cast->p[position].key == (void*)-1 /* Deleted */ \
        || cast->p[position].hash != hash || strcmp(cast->p[position].key, key) != 0) /* Non-match */ \
        { \
            position = (position + 1) & mask; \
        } \
        else /* Match */ \
        { \
            memcpy(data, &cast->p[position].p, sizeof(cast->p[position].p)); \
            return true; \
        } \
    } \
}

#define IMPLEMENT_GENERIC_HASH_MAP_ERASE(FRIENDLY_UPPER) \
{ \
    struct FRIENDLY_UPPER ## HashMap *cast = (struct FRIENDLY_UPPER ## HashMap*)map; \
    size_t hash = fnv1a(key); \
    size_t mask = cast->capacity - 1; \
    size_t position = hash & mask; \
    while (true) \
    { \
        if (cast->p[position].key == (void*)0) /* Ivalid */ \
        { \
            return false; \
        } \
        else if (cast->p[position].key == (void*)-1 /* Deleted */ \
        || cast->p[position].hash != hash || strcmp(cast->p[position].key, key) != 0) /* Non-match */ \
        { \
            position = (position + 1) & mask; \
        } \
        else /* Match */ \
        { \
            size_t chain_length, end_chain_position; \
            free(cast->p[position].key); \
            cast->size--; \
            chain_length = 0; \
            while (cast->p[(position + chain_length + 1) & mask].hash != (size_t)-1) chain_length++; \
            if (chain_length == 0) /* Element can be erased completely */ \
            { \
                cast->p[position].key = (void*)0; \
                return true; \
            } \
            end_chain_position = (position + chain_length) & mask; \
            if ((cast->p[end_chain_position].hash & mask) == position) /* Last element can be brought to beginning */ \
            { \
                cast->p[position].hash = cast->p[end_chain_position].hash; \
                cast->p[position].key = cast->p[end_chain_position].key; \
                cast->p[position].p = cast->p[end_chain_position].p; \
                cast->p[end_chain_position].key = (void*)0; \
                return true; \
            } \
            /* Nothing can be done, leave deleted element */ \
            cast->p[position].key = (void*)-1; \
            cast->deleted++; \
            return true; \
        } \
    } \
}

#define IMPLEMENT_GENERIC_HASH_MAP_INSERT(FRIENDLY_UPPER) \
{ \
    struct FRIENDLY_UPPER ## HashMap *cast = (struct FRIENDLY_UPPER ## HashMap*)map; \
    if (2 * (cast->size + cast->deleted + 1) > cast->capacity) \
    { \
        /* Rehash */ \
        const size_t required_capacity = 2 * (cast->size + 1); \
        size_t new_capacity = 1; \
        size_t new_mask; \
        size_t position; \
        struct FRIENDLY_UPPER ## HashMapEntry *new_p; \
        while (new_capacity < required_capacity) new_capacity = (new_capacity << 1); \
        new_mask = new_capacity - 1; \
        new_p = malloc(new_capacity * sizeof(struct FRIENDLY_UPPER ## HashMapEntry)); \
        ARET(new_p != NULL); \
        for (position = 0; position < new_capacity; position++) \
        { \
            new_p[position].key = NULL; /* Invalid */ \
        } \
        for (position = 0; position < cast->capacity; position++) \
        { \
            size_t new_position; \
            if (cast->p[position].key == NULL || cast->p[position].key == (void*)-1) continue; /* Deleted or invalid */ \
            new_position = cast->p[position].hash & new_mask; \
            while (true) \
            { \
                if (new_p[new_position].key == NULL) /* Invalid */ \
                { \
                    new_p[new_position].hash = cast->p[position].hash; \
                    new_p[new_position].key = cast->p[position].key; \
                    new_p[new_position].p = cast->p[position].p; \
                    break; \
                } \
                else /* Deleted or valid */ \
                { \
                    new_position = (new_position + 1) & new_mask; \
                } \
            } \
        } \
        free(cast->p); \
        cast->p = new_p; \
        cast->capacity = new_capacity; \
        cast->deleted = 0; \
    } \
    { \
        const size_t hash = fnv1a(key); \
        const size_t mask = cast->capacity - 1; \
        size_t position = hash & mask; \
        while (true) \
        { \
            if (cast->p[position].key == NULL) /* Ivalid */ \
            { \
                const size_t key_size = strlen(key); \
                cast->p[position].key = malloc(key_size + 1); \
                ARET(cast->p[position].key != NULL); \
                memcpy(cast->p[position].key, key, key_size + 1); \
                cast->p[position].hash = hash; \
                cast->p[position].p = data; \
                cast->size++; \
                ERROR_RETURN_OK(); /* New key */ \
            } \
            else if (cast->p[position].key == (void*)-1 /* Deleted */ \
            || cast->p[position].hash != hash || strcmp(cast->p[position].key, key) != 0) /* Non-match */ \
            { \
                position = (position + 1) & mask; \
            } \
            else /* Match */ \
            { \
                cast->p[position].p = data; \
                ERROR_RETURN_OK(); /* Key overwrite */ \
            } \
        } \
    } \
}

static size_t fnv1a(const char *key)
{
    /* http://www.isthe.com/chongo/tech/comp/fnv/ */
    
    if (sizeof(size_t) == 8)
    {
        const size_t prime = 1099511628211;
        size_t value;
        value = 3421674724; /* 14695981039346656037 = 3421674724 * 2^32 + 2216829733 */
        value <<= 32;
        value += 2216829733;
        for (; *key != '\0'; key++)
        {
            value ^= (size_t)(*key);
            value *= prime;
        }
        return value;
    }
    else
    {
        const size_t prime = 16777619;
        size_t value = 2166136261;
        for (; *key != '\0'; key++)
        {
            value ^= (size_t)(*key);
            value *= prime;
        }
        return value;
    }
}

void generic_hmap_finalize_1(void *map)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(Generic1Byte)
void generic_hmap_finalize_2(void *map)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(Generic2Byte)
void generic_hmap_finalize_4(void *map)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(Generic4Byte)
void generic_hmap_finalize_8(void *map)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(Generic8Byte)
void generic_hmap_finalize_n(void *map, size_t entry_sizeof)
{ (void)map; (void)entry_sizeof; } /*TODO*/

bool generic_hmap_read_1(const void *map, const char *key, void *data)
IMPLEMENT_GENERIC_HASH_MAP_FIND(Generic1Byte)
bool generic_hmap_read_2(const void *map, const char *key, void *data)
IMPLEMENT_GENERIC_HASH_MAP_FIND(Generic2Byte)
bool generic_hmap_read_4(const void *map, const char *key, void *data)
IMPLEMENT_GENERIC_HASH_MAP_FIND(Generic4Byte)
bool generic_hmap_read_8(const void *map, const char *key, void *data)
IMPLEMENT_GENERIC_HASH_MAP_FIND(Generic8Byte)
bool generic_hmap_read_n(const void *map, const char *key, void *data, size_t entry_sizeof)
{ (void)map; (void)key; (void)data; (void)entry_sizeof; return false; } /*TODO*/

bool generic_hmap_erase_1(void *map, const char *key)
IMPLEMENT_GENERIC_HASH_MAP_ERASE(Generic1Byte)
bool generic_hmap_erase_2(void *map, const char *key)
IMPLEMENT_GENERIC_HASH_MAP_ERASE(Generic2Byte)
bool generic_hmap_erase_4(void *map, const char *key)
IMPLEMENT_GENERIC_HASH_MAP_ERASE(Generic4Byte)
bool generic_hmap_erase_8(void *map, const char *key)
IMPLEMENT_GENERIC_HASH_MAP_ERASE(Generic8Byte)
bool generic_hmap_erase_n(void *map, const char *key, size_t entry_sizeof)
{ (void)map; (void)key; (void)entry_sizeof; return false; } /*TODO*/

ERROR_TYPE generic_hmap_write_1(void *map, const char *key, GENERIC_ARGMENT_1 data)
IMPLEMENT_GENERIC_HASH_MAP_INSERT(Generic1Byte)
ERROR_TYPE generic_hmap_write_2(void *map, const char *key, GENERIC_ARGMENT_2 data)
IMPLEMENT_GENERIC_HASH_MAP_INSERT(Generic2Byte)
ERROR_TYPE generic_hmap_write_4(void *map, const char *key, GENERIC_ARGMENT_4 data)
IMPLEMENT_GENERIC_HASH_MAP_INSERT(Generic4Byte)
ERROR_TYPE generic_hmap_write_8(void *map, const char *key, GENERIC_ARGMENT_8 data)
IMPLEMENT_GENERIC_HASH_MAP_INSERT(Generic8Byte)
