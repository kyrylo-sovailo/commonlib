#ifndef COMMONLIB_CHAR_HASH_MAP_H
#define COMMONLIB_CHAR_HASH_MAP_H

#include "char.h"
#include "hash_map.h"

DECLARE_HASH_MAP(cchar_t, CharBuffer)
DECLARE_HASH_MAP_INITIALIZE(cchar_t, CharBuffer, char_hmap_)
DECLARE_HASH_MAP_FINALIZE(cchar_t, CharBuffer, char_hmap_)
DECLARE_HASH_MAP_VALID(cchar_t, CharBuffer, char_hmap_)
DECLARE_HASH_MAP_ACCESS(cchar_t, CharBuffer, char_hmap_)
DECLARE_HASH_MAP_DELETE(cchar_t, CharBuffer, char_hmap_)

#endif
