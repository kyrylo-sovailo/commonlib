#ifndef HASH_MAP_IMPLEMENTATION_H
#define HASH_MAP_IMPLEMENTATION_H

#include "hash_map.h"

#define IMPLEMENT_HASH_MAP_FINALIZE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
void FRIENDLY_LOWER ## _hmap_finalize(struct FRIENDLY_UPPER ## HashMap *map) \
{ \
    if (sizeof(map->p->p) == 1) generic_hmap_finalize_1(map); \
    else if (sizeof(map->p->p) == 2) generic_hmap_finalize_2(map); \
    else if (sizeof(map->p->p) == 4) generic_hmap_finalize_4(map); \
    else if (sizeof(map->p->p) == 8) generic_hmap_finalize_8(map); \
    else generic_hmap_finalize(sizeof(*map->p), map); \
}
#define IMPLEMENT_HASH_MAP_READ(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
bool FRIENDLY_LOWER ## _hmap_read(const struct FRIENDLY_UPPER ## HashMap *map, const char *key, TYPE *data) \
{ \
    if (sizeof(map->p->p) == 1) return generic_hmap_read_1(map, key, data); \
    else if (sizeof(map->p->p) == 2) return generic_hmap_read_2(map, key, data); \
    else if (sizeof(map->p->p) == 4) return generic_hmap_read_4(map, key, data); \
    else if (sizeof(map->p->p) == 8) return generic_hmap_read_8(map, key, data); \
    else return generic_hmap_read(sizeof(*map->p), map, key, data); \
}
#define IMPLEMENT_HASH_MAP_ERASE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER) \
bool FRIENDLY_LOWER ## _hmap_erase(struct FRIENDLY_UPPER ## HashMap *map, const char *key) \
{ \
    if (sizeof(map->p->p) == 1) return generic_hmap_erase_1(map, key); \
    else if (sizeof(map->p->p) == 2) return generic_hmap_erase_2(map, key); \
    else if (sizeof(map->p->p) == 4) return generic_hmap_erase_4(map, key); \
    else if (sizeof(map->p->p) == 8) return generic_hmap_erase_8(map, key); \
    else return generic_hmap_erase(sizeof(*map->p), map, key); \
}
#define IMPLEMENT_HASH_MAP_WRITE(TYPE, FRIENDLY_UPPER, FRIENDLY_LOWER, SIZE) \
ERROR_TYPE FRIENDLY_LOWER ## _hmap_write(struct FRIENDLY_UPPER ## HashMap *map, const char *key, TYPE data) \
{ \
    struct Error *check[(sizeof(map->p->p) == SIZE) ? 1 : -1]; \
    check[0] = generic_hmap_write_ ## SIZE(map, key, (GENERIC_ARGMENT_ ## SIZE)data); \
    return check[0]; \
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
