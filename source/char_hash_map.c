#include "../include/char_hash_map.h"
#include "../include/hash_map_implementation.h"

/*
TODO: do something with initialization
static void char_hmap_initialize_element(char *p) { (void)p; }
*/
static void char_hmap_finalize_element(cchar_t *p) { (void)p; }

IMPLEMENT_HASH_MAP_INITIALIZE(cchar_t, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_FINALIZE(cchar_t, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_VALID(cchar_t, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_ACCESS(cchar_t, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_DELETE(cchar_t, CharBuffer, char_hmap_)
