#ifndef RING_H
#define RING_H

#include "char_buffer.h"
#include "error.h"

struct Ring
{
    struct CharBuffer buffer;
    char *begin, *end;
};

struct RingConstWindow
{
    const char *p;
    size_t size;
};

struct RingWindow
{
    char *p;
    size_t size;
};

/* Gets the size of the ring */
size_t ring_size(const struct Ring *ring);

/* Allocates space for N more bytes */
ERROR_TYPE ring_push(struct Ring *ring, size_t size) NODISCARD;

/* Removes first N bytes */
ERROR_TYPE ring_pop(struct Ring *ring, size_t size) NODISCARD;

/* Grants access to the first N bytes */
ERROR_TYPE ring_get(const struct Ring *ring, size_t size, struct RingConstWindow windows[2], unsigned char *window_number) NODISCARD;

/* Grants access to the last N bytes */
ERROR_TYPE ring_get_last(const struct Ring *ring, size_t size, struct RingConstWindow windows[2], unsigned char *window_number) NODISCARD;

/* Grants access to all available bytes */
void ring_get_all(const struct Ring *ring, struct RingConstWindow windows[2], unsigned char *window_number);

/* Removes all bytes, but does not finalize the buffer */
void ring_clear(struct Ring *ring);

#endif
