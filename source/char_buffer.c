#include "../include/char_buffer.h"
#include "../include/buffer_implementation.h"

static void char_buffer_initialize_element(char *p) { (void)p; }
static void char_buffer_finalize_element(char *p) { (void)p; }

IMPLEMENT_BUFFER_INITIALIZE(char, CharBuffer, char_buffer_)
IMPLEMENT_BUFFER_FINALIZE(char, CharBuffer, char_buffer_)
IMPLEMENT_BUFFER_RESIZE(char, CharBuffer, char_buffer_)
IMPLEMENT_BUFFER_RESERVE(char, CharBuffer, char_buffer_)
IMPLEMENT_BUFFER_APPEND(char, CharBuffer, char_buffer_)
IMPLEMENT_BUFFER_PUSH(char, CharBuffer, char_buffer_, 1)