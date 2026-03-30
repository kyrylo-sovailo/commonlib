#include "../include/char_hmap.h"
#include "../include/hash_map_implementation.h"

/*
TODO: do something with initialization
static void char_hmap_initialize_element(char *p) { (void)p; }
*/
static void char_hmap_finalize_element(char *p) { (void)p; }

IMPLEMENT_HASH_MAP_INITIALIZE(char, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_FINALIZE(char, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_VALID(char, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_ACCESS(char, CharBuffer, char_hmap_)
IMPLEMENT_HASH_MAP_DELETE(char, CharBuffer, char_hmap_)
