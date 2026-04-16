#include "../include/hash_map_implementation.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef COMMON_WCHAR
    #include <wchar.h>
#endif

#define INVALID ((cchar_t*)0)
#define DELETED ((cchar_t*)-1)

static size_t make_number(unsigned short a48, unsigned short a32, unsigned short a16, unsigned short a0)
{
    size_t number = a48;
    number <<= 16;
    number |= a32;
    number <<= 16;
    number |= a16;
    number <<= 16;
    number |= a0;
    return number;
}

static size_t fnv1a(const cchar_t *key)
{
    /* http://www.isthe.com/chongo/tech/comp/fnv/ */

    size_t prime, value;
    if (sizeof(size_t) == 8)
    {
        /* 1099511628211 */
        prime = make_number(0, 256, 0, 435);
        /* 14695981039346656037 */
        value = make_number(52210, 40164, 33826, 8997);
    }
    else
    {
        /* 16777619 */
        prime = make_number(0, 0, 256, 403);
        /* 2166136261 */
        value = make_number(0, 0, 33052, 40389);
    }
    
    for (; *key != '\0'; key++)
    {
        value ^= (size_t)(*key);
        value *= prime;
    }
    return value;
}

DECLARE_HASH_MAP(GENERIC_ARGMENT_1, GenericByteHMap)
DECLARE_HASH_MAP(GENERIC_ARGMENT_2, GenericWordHMap)
DECLARE_HASH_MAP(GENERIC_ARGMENT_4, GenericDWordHMap)
DECLARE_HASH_MAP(GENERIC_ARGMENT_8, GenericQWordHMap)

void generic_hmap_initialize(void *hmap)
{
    const struct GenericByteHMap zero = ZERO_INIT; \
    struct GenericByteHMap *cast = (struct GenericByteHMap*)hmap; \
    *cast = zero;
}

#define IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(STRUCT_NAME, POSITION_EXPRESSION) \
{ \
    const struct STRUCT_NAME zero = ZERO_INIT; \
    struct STRUCT_NAME *cast = (struct STRUCT_NAME*)hmap; \
    size_t position; \
    for (position = 0; position < cast->capacity; position++) \
    { \
        if (POSITION_EXPRESSION->key != INVALID && POSITION_EXPRESSION->key != DELETED) free(POSITION_EXPRESSION->key); \
    } \
    if (cast->p != NULL) free(cast->p); \
    *cast = zero; \
}
void generic_hmap_finalize_1(void *hmap)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(GenericByteHMap, (&cast->p[position]))
void generic_hmap_finalize_2(void *hmap)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(GenericWordHMap, (&cast->p[position]))
void generic_hmap_finalize_4(void *hmap)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(GenericDWordHMap, (&cast->p[position]))
void generic_hmap_finalize_8(void *hmap)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(GenericQWordHMap, (&cast->p[position]))
void generic_hmap_finalize_n(void *hmap, size_t entry_sizeof)
IMPLEMENT_GENERIC_HASH_MAP_FINALIZE(GenericByteHMap, ((struct GenericByteHMapEntry*)(((char*)cast->p) + position * entry_sizeof)))

bool generic_hmap_valid(void *entry)
{
    struct GenericByteHMapEntry *cast = (struct GenericByteHMapEntry*)entry;
    return cast->key != INVALID && cast->key != DELETED;
}

#define IMPLEMENT_GENERIC_HASH_MAP_ACCESS(STRUCT_NAME, SIZE_EXPRESSION, POSITION_EXPRESSION, NEW_POSITION_EXPRESSION) \
{ \
    struct STRUCT_NAME *cast = (struct STRUCT_NAME*)hmap; \
    struct STRUCT_NAME ## Entry **entry_cast = (struct STRUCT_NAME ## Entry**)entry; \
    if (2 * (cast->size + cast->deleted + 1) > cast->capacity) \
    { \
        /* Rehash */ \
        const size_t required_capacity = 2 * (cast->size + 1); \
        size_t new_capacity = 1; \
        size_t new_mask; \
        size_t position, new_position; \
        struct STRUCT_NAME ## Entry *new_p; \
        while (new_capacity < required_capacity) new_capacity *= 2; \
        new_mask = new_capacity - 1; \
        new_p = (struct STRUCT_NAME ## Entry*)malloc(new_capacity * SIZE_EXPRESSION); \
        ARET(new_p != NULL); \
        for (new_position = 0; new_position < new_capacity; new_position++) \
        { \
            NEW_POSITION_EXPRESSION->key = INVALID; /* Invalid */ \
        } \
        for (position = 0; position < cast->capacity; position++) \
        { \
            if (POSITION_EXPRESSION->key == INVALID || POSITION_EXPRESSION->key == DELETED) continue; /* Deleted or invalid */ \
            new_position = POSITION_EXPRESSION->hash & new_mask; \
            while (true) \
            { \
                if (NEW_POSITION_EXPRESSION->key == INVALID) /* Invalid */ \
                { \
                    memcpy(NEW_POSITION_EXPRESSION, POSITION_EXPRESSION, SIZE_EXPRESSION); \
                    break; \
                } \
                else /* Valid (deleted is impossible) */ \
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
            if (POSITION_EXPRESSION->key == INVALID) /* Invalid */ \
            { \
                if (create) \
                { \
                    const size_t key_size = COMMON_WCS(len(key)) + 1; \
                    cchar_t *new_key = (cchar_t*)malloc(key_size * sizeof(*new_key)); \
                    ARET(new_key != NULL); \
                    COMMON_W(memcpy(new_key, key, key_size)); \
                    POSITION_EXPRESSION->key = new_key; \
                    POSITION_EXPRESSION->hash = hash; \
                    cast->size++; \
                    *entry_cast = POSITION_EXPRESSION; \
                } \
                else \
                { \
                    *entry_cast = NULL; \
                } \
                break; \
            } \
            else if (POSITION_EXPRESSION->key == DELETED /* Deleted */ \
            || POSITION_EXPRESSION->hash != hash || COMMON_WCS(cmp(POSITION_EXPRESSION->key, key) != 0)) /* Non-match */ \
            { \
                position = (position + 1) & mask; \
            } \
            else /* Match */ \
            { \
                *entry_cast = POSITION_EXPRESSION; \
            } \
        } \
        ERROR_RETURN_OK(); \
    } \
}
ERROR_TYPE generic_hmap_access_1(void *hmap, const cchar_t *key, void *entry, bool create)
IMPLEMENT_GENERIC_HASH_MAP_ACCESS(GenericByteHMap, sizeof(cast->p->p), (&cast->p[position]), (&new_p[new_position]))
ERROR_TYPE generic_hmap_access_2(void *hmap, const cchar_t *key, void *entry, bool create)
IMPLEMENT_GENERIC_HASH_MAP_ACCESS(GenericWordHMap, sizeof(cast->p->p), (&cast->p[position]), (&new_p[new_position]))
ERROR_TYPE generic_hmap_access_4(void *hmap, const cchar_t *key, void *entry, bool create)
IMPLEMENT_GENERIC_HASH_MAP_ACCESS(GenericDWordHMap, sizeof(cast->p->p), (&cast->p[position]), (&new_p[new_position]))
ERROR_TYPE generic_hmap_access_8(void *hmap, const cchar_t *key, void *entry, bool create)
IMPLEMENT_GENERIC_HASH_MAP_ACCESS(GenericQWordHMap, sizeof(cast->p->p), (&cast->p[position]), (&new_p[new_position]))
ERROR_TYPE generic_hmap_access_n(void *hmap, const cchar_t *key, void *entry, bool create, size_t entry_sizeof)
IMPLEMENT_GENERIC_HASH_MAP_ACCESS(GenericByteHMap, entry_sizeof, ((struct GenericByteHMapEntry*)(((char*)cast->p) + position * entry_sizeof)), ((struct GenericByteHMapEntry*)(((char*)new_p) + new_position * entry_sizeof)))

#define IMPLEMENT_GENERIC_HASH_MAP_DELETE(STRUCT_NAME, POSITION_EXPRESSION) \
{ \
    struct STRUCT_NAME *cast = (struct STRUCT_NAME*)hmap; \
    struct STRUCT_NAME ## Entry *entry_cast = (struct STRUCT_NAME ## Entry*)entry; \
    size_t mask; \
    size_t position; \
    if (entry_cast->key == INVALID || entry_cast->key == DELETED) return; /* Invalid or deleted */ \
    free(entry_cast->key); \
    mask = cast->capacity - 1; \
    position = (size_t)(entry_cast - cast->p); \
    position = (position + 1) & mask; \
    if (POSITION_EXPRESSION->key == INVALID) \
    { \
        entry_cast->key = INVALID;  /* Next entry is invalid, there is no chain, can delete completely */ \
    } \
    else \
    { \
        entry_cast->key = DELETED;  /* Next entry is deleted or valid, there is chain, must mark as deleted */ \
        cast->deleted++;            /* Another thing I could do is relocate last element to beginning, but that would be element relocation, so I deleted it */ \
    } \
}

void generic_hmap_delete_1(void *hmap, void *entry)
IMPLEMENT_GENERIC_HASH_MAP_DELETE(GenericByteHMap, (&cast->p[position]))
void generic_hmap_delete_2(void *hmap, void *entry)
IMPLEMENT_GENERIC_HASH_MAP_DELETE(GenericWordHMap, (&cast->p[position]))
void generic_hmap_delete_4(void *hmap, void *entry)
IMPLEMENT_GENERIC_HASH_MAP_DELETE(GenericDWordHMap, (&cast->p[position]))
void generic_hmap_delete_8(void *hmap, void *entry)
IMPLEMENT_GENERIC_HASH_MAP_DELETE(GenericQWordHMap, (&cast->p[position]))
void generic_hmap_delete_n(void *hmap, void *entry, size_t entry_sizeof)
IMPLEMENT_GENERIC_HASH_MAP_DELETE(GenericQWordHMap, ((struct GenericByteHMapEntry*)(((char*)cast->p) + position * entry_sizeof)))
