#include "../include/output.h"

#include <stdarg.h>
#include <stdio.h>

void output_open()
{
    /* Nothing to do */
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

void output_close()
{
    fflush(stderr);
}