#ifndef COMMONLIB_CHAR_H
#define COMMONLIB_CHAR_H

/*
The library takes nativist approach and uses cchars unless explicitly specified.
NCHAR = narrow char         (exists everywhere)
WCHAR = wide character      (exists only on Windows)
CCHAR = common character    (exists everywhere, defined differently)
 CHAR = common character    (exists everywhere, defined differently)
*/

#ifdef WIN32
    #include <stddef.h>     /* Wide   */
    typedef char nchar_t;   /* Narrow */
    typedef wchar_t cchar_t;/* Common */

    #define COMMON_WCHAR
    #define COMMON_W(FUNCTION) w##FUNCTION      /* Prefix for standard C string functions */
    #define COMMON_W2(FUNCTION) wcs##FUNCTION   /* Prefix for standard C string functions */
    #define COMMON_L(TEXT) L##TEXT              /* Prefix for text and characters */
    #define COMMON_C L"%lc"                     /* Character-dependent formatting sequence for common character */
    #define COMMON_S L"%ls"                     /* Character-dependent formatting sequence for common string */
    #define COMMON_SEPARATOR L'\\'              /* Filesystem separator character */
    #define COMMON_SEPARATOR_STR L"\\"          /* Filesystem separator string */
#else
                            /* Wide   */
    typedef char nchar_t;   /* Narrow */
    typedef char cchar_t;   /* Common */

    #define COMMON_W(FUNCTION) FUNCTION
    #define COMMON_W2(FUNCTION) str##FUNCTION
    #define COMMON_L(TEXT) TEXT
    #define COMMON_C "%c"
    #define COMMON_S "%s"
    #define COMMON_SEPARATOR '\\'
    #define COMMON_SEPARATOR_STR "\\"
#endif

#endif
