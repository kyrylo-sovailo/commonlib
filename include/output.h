#ifndef OUTPUT_H
#define OUTPUT_H

#include "macro.h"

#include <stdarg.h>
#include <stddef.h>

#ifdef ERROR_TRACE
/*
Available only in ERROR_TRACE because other ones don't print errors in one function
but transfer the control to the user instead
*/

/* Opens error output (guaranteed to succeed) */
void output_open();

/* Closes error output (guaranteed to succeed) */
void output_close();
#endif

/* Writes message to error output (guaranteed to succeed) */
void output_print(const char *format, ...) PRINTFLIKE(1, 2);

/* Writes message to error output (guaranteed to succeed) */
void output_vprint(const char *format, va_list va) PRINTFLIKE(1, 0);

#endif
