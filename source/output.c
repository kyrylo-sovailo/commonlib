#include "../include/output.h"

#include <stdarg.h>
#include <stdio.h>

void output_initialize(void)
{
    /* Nothing to do */
}
 
void output_finalize(void)
{
    /* Nothing to do */
}

void output_open(void)
{
    /* Nothing to do */
}

void output_close(void)
{
    fflush(stderr);
}

void output_print(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    output_vprint(format, va);
    va_end(va);
}

void output_vprint(const char *format, va_list va)
{
    vfprintf(stderr, format, va);
}
