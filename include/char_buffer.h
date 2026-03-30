#ifndef CHAR_BUFFER_H
#define CHAR_BUFFER_H

#include "buffer.h"

DECLARE_BUFFER(char, CharBuffer)
DECLARE_BUFFER_INITIALIZE(char, CharBuffer, char_buffer_)
DECLARE_BUFFER_FINALIZE(char, CharBuffer, char_buffer_)
DECLARE_BUFFER_RESIZE(char, CharBuffer, char_buffer_)
DECLARE_BUFFER_RESERVE(char, CharBuffer, char_buffer_)
DECLARE_BUFFER_APPEND(char, CharBuffer, char_buffer_)
DECLARE_BUFFER_PUSH(char, CharBuffer, char_buffer_)

#endif
