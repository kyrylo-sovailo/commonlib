#ifndef COMMONLIB_OUTPUT_H
#define COMMONLIB_OUTPUT_H

#include "macro.h"

#include <stdarg.h>
#include <stddef.h>

/* Initializes/finalizes output module (guaranteed to succeed) */
void output_module_initialize(void);
void output_module_finalize(void);

/* Opens error output (guaranteed to succeed) */
void output_open(void);

/* Closes error output (guaranteed to succeed) */
void output_close(void);

/* Writes message to error output (guaranteed to succeed) */
void output_print(const char *format, ...) PRINTFLIKE(1, 2);

/* Writes message to error output (guaranteed to succeed) */
void output_vprint(const char *format, va_list va) PRINTFLIKE(1, 0);

/* Write timestamp to error output (guaranteed to succeed) */
void output_print_time(void);

#endif
