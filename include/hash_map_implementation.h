#ifndef COMMONLIB_HASH_MAP_IMPLEMENTATION_H
#define COMMONLIB_HASH_MAP_IMPLEMENTATION_H

#include "hash_map.h"

#define IMPLEMENT_HASH_MAP_INITIALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## initialize(struct STRUCT_NAME *hmap) \
{ \
    generic_hmap_initialize(hmap); \
}

#define IMPLEMENT_HASH_MAP_FINALIZE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## finalize(struct STRUCT_NAME *hmap) \
{ \
    struct STRUCT_NAME ## Entry *entry; \
    for (entry = hmap->p; entry < hmap->p + hmap->capacity; entry++) \
    { \
        if (generic_hmap_valid(entry)) FUNCTION_NAME ## finalize_element(&entry->p); \
    } \
    switch (sizeof(hmap->p->p)) \
    { \
    case 1: generic_hmap_finalize_1(hmap); break; \
    case 2: generic_hmap_finalize_2(hmap); break; \
    case 4: generic_hmap_finalize_4(hmap); break; \
    case 8: generic_hmap_finalize_8(hmap); break; \
    default: generic_hmap_finalize_n(hmap, sizeof(*hmap->p)); break; \
    } \
}

#define IMPLEMENT_HASH_MAP_VALID(TYPE, STRUCT_NAME, FUNCTION_NAME) \
bool FUNCTION_NAME ## valid(struct STRUCT_NAME ## Entry *entry) \
{ \
    return generic_hmap_valid(entry); \
}

#define IMPLEMENT_HASH_MAP_ACCESS(TYPE, STRUCT_NAME, FUNCTION_NAME) \
ERROR_TYPE FUNCTION_NAME ## access(struct STRUCT_NAME *hmap, const cchar_t *key, struct STRUCT_NAME ## Entry **entry, bool create) \
{ \
    ERROR_DECLARE(); \
    switch (sizeof(hmap->p->p)) \
    { \
    case 1: ERROR_ASSIGN(generic_hmap_access_1(hmap, key, entry, create)); break; \
    case 2: ERROR_ASSIGN(generic_hmap_access_2(hmap, key, entry, create)); break; \
    case 4: ERROR_ASSIGN(generic_hmap_access_4(hmap, key, entry, create)); break; \
    case 8: ERROR_ASSIGN(generic_hmap_access_8(hmap, key, entry, create)); break; \
    default: ERROR_ASSIGN(generic_hmap_access_n(hmap, key, entry, create, sizeof(*hmap->p))); break; \
    } \
    ERROR_RETURN(); \
}

#define IMPLEMENT_HASH_MAP_DELETE(TYPE, STRUCT_NAME, FUNCTION_NAME) \
void FUNCTION_NAME ## delete(struct STRUCT_NAME *hmap, struct STRUCT_NAME ## Entry *entry) \
{ \
    FUNCTION_NAME ## finalize_element(&entry->p); \
    switch (sizeof(hmap->p->p)) \
    { \
    case 1: generic_hmap_delete_1(hmap, entry); break; \
    case 2: generic_hmap_delete_2(hmap, entry); break; \
    case 4: generic_hmap_delete_4(hmap, entry); break; \
    case 8: generic_hmap_delete_8(hmap, entry); break; \
    default: generic_hmap_delete_n(hmap, entry, sizeof(*hmap->p)); break; \
    } \
}

void generic_hmap_initialize(void *hmap);

void generic_hmap_finalize_1(void *hmap);
void generic_hmap_finalize_2(void *hmap);
void generic_hmap_finalize_4(void *hmap);
void generic_hmap_finalize_8(void *hmap);
void generic_hmap_finalize_n(void *hmap, size_t entry_sizeof);

bool generic_hmap_valid(void *entry);

ERROR_TYPE generic_hmap_access_1(void *hmap, const cchar_t *key, void *entry, bool create);
ERROR_TYPE generic_hmap_access_2(void *hmap, const cchar_t *key, void *entry, bool create);
ERROR_TYPE generic_hmap_access_4(void *hmap, const cchar_t *key, void *entry, bool create);
ERROR_TYPE generic_hmap_access_8(void *hmap, const cchar_t *key, void *entry, bool create);
ERROR_TYPE generic_hmap_access_n(void *hmap, const cchar_t *key, void *entry, bool create, size_t entry_sizeof);

void generic_hmap_delete_1(void *hmap, void *entry);
void generic_hmap_delete_2(void *hmap, void *entry);
void generic_hmap_delete_4(void *hmap, void *entry);
void generic_hmap_delete_8(void *hmap, void *entry);
void generic_hmap_delete_n(void *hmap, void *entry, size_t entry_sizeof);

#endif
