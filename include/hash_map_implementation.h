#ifndef HASH_MAP_IMPLEMENTATION_H
#define HASH_MAP_IMPLEMENTATION_H

#include "hash_map.h"

#define IMPLEMENT_HASH_MAP_FINALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## finalize(struct STRUCT_NAME *map) \
{ \
    switch (sizeof(map->p->p) == 1) \
    { \
    case 1: generic_hmap_finalize_1(map); break; \
    case 2: generic_hmap_finalize_2(map); break; \
    case 4: generic_hmap_finalize_4(map); break; \
    case 8: generic_hmap_finalize_8(map); break; \
    default: generic_hmap_finalize(sizeof(*map->p), map); break; \
    } \
}
#define IMPLEMENT_HASH_MAP_READ(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## read(const struct STRUCT_NAME *map, const char *key, TYPE *data) \
{ \
    switch (sizeof(map->p->p) == 1) \
    { \
    case 1: return generic_hmap_read_1(map, key, data); \
    case 2: return generic_hmap_read_2(map, key, data); \
    case 4: return generic_hmap_read_4(map, key, data); \
    case 8: return generic_hmap_read_8(map, key, data); \
    default: return generic_hmap_read(sizeof(*map->p), map, key, data); \
    } \
}
#define IMPLEMENT_HASH_MAP_ERASE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## erase(struct STRUCT_NAME *map, const char *key) \
{ \
    switch (sizeof(map->p->p) == 1) \
    { \
    case 1: return generic_hmap_erase_1(map, key); \
    case 2: return generic_hmap_erase_1(map, key); \
    case 4: return generic_hmap_erase_1(map, key); \
    case 8: return generic_hmap_erase_1(map, key); \
    default: return generic_hmap_erase(sizeof(*map->p), map, key); \
    } \
}
#define IMPLEMENT_HASH_MAP_WRITE(TYPE, STRUCT_NAME, FUNCTION_NAME, SIZE) \
ERROR_TYPE FUNCTION_NAME ## write(struct STRUCT_NAME *map, const char *key, TYPE data) \
{ \
    ERROR_TYPE static_check[(sizeof(map->p->p) == SIZE) ? 1 : -1]; \
    (void)static_check; \
    ERROR_RETURN_OPERATOR() generic_hmap_write_ ## SIZE(map, key, (GENERIC_ARGMENT_ ## SIZE)data); \
}

void generic_hmap_finalize_1(void *map);
void generic_hmap_finalize_2(void *map);
void generic_hmap_finalize_4(void *map);
void generic_hmap_finalize_8(void *map);
void generic_hmap_finalize_n(void *map, size_t entry_sizeof);

bool generic_hmap_read_1(const void *map, const char *key, void *data);
bool generic_hmap_read_2(const void *map, const char *key, void *data);
bool generic_hmap_read_4(const void *map, const char *key, void *data);
bool generic_hmap_read_8(const void *map, const char *key, void *data);
bool generic_hmap_read_n(const void *map, const char *key, void *data, size_t entry_sizeof);

bool generic_hmap_erase_1(void *map, const char *key);
bool generic_hmap_erase_2(void *map, const char *key);
bool generic_hmap_erase_4(void *map, const char *key);
bool generic_hmap_erase_8(void *map, const char *key);
bool generic_hmap_erase_n(void *map, const char *key, size_t entry_sizeof);

ERROR_TYPE generic_hmap_write_1(void *map, const char *key, GENERIC_ARGMENT_1 data);
ERROR_TYPE generic_hmap_write_2(void *map, const char *key, GENERIC_ARGMENT_2 data);
ERROR_TYPE generic_hmap_write_4(void *map, const char *key, GENERIC_ARGMENT_4 data);
ERROR_TYPE generic_hmap_write_8(void *map, const char *key, GENERIC_ARGMENT_8 data);

#endif
