#ifndef COMMONLIB_OUTPUT_H
#define COMMONLIB_OUTPUT_H

#include "bool.h"
#include "char.h"
#include "macro.h"

#include <stdarg.h>
#include <stddef.h>

#ifdef WIN32
    #define COLOR_BLACK           0
    #define COLOR_RED             FOREGROUND_RED
    #define COLOR_GREEN           FOREGROUND_GREEN
    #define COLOR_YELLOW          FOREGROUND_RED | FOREGROUND_GREEN
    #define COLOR_BLUE            FOREGROUND_BLUE
    #define COLOR_MAGENTA         FOREGROUND_RED | FOREGROUND_BLUE
    #define COLOR_CYAN            FOREGROUND_GREEN | FOREGROUND_BLUE
    #define COLOR_WHITE           FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    #define COLOR_BRIGHT_BLACK    FOREGROUND_INTENSITY
    #define COLOR_BRIGHT_RED      FOREGROUND_INTENSITY | FOREGROUND_RED
    #define COLOR_BRIGHT_GREEN    FOREGROUND_INTENSITY | FOREGROUND_GREEN
    #define COLOR_BRIGHT_YELLOW   FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
    #define COLOR_BRIGHT_BLUE     FOREGROUND_INTENSITY | FOREGROUND_BLUE
    #define COLOR_BRIGHT_MAGENTA  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
    #define COLOR_BRIGHT_CYAN     FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
    #define COLOR_BRIGHT_WHITE    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    typedef unsigned short ccolor_t;
#else
    #define COLOR_BLACK           "\x1b[00;30m"
    #define COLOR_RED             "\x1b[00;31m"
    #define COLOR_GREEN           "\x1b[00;32m"
    #define COLOR_YELLOW          "\x1b[00;33m"
    #define COLOR_BLUE            "\x1b[00;34m"
    #define COLOR_MAGENTA         "\x1b[00;35m"
    #define COLOR_CYAN            "\x1b[00;36m"
    #define COLOR_WHITE           "\x1b[00;37m"
    #define COLOR_BRIGHT_BLACK    "\x1b[01;30m"
    #define COLOR_BRIGHT_RED      "\x1b[01;31m"
    #define COLOR_BRIGHT_GREEN    "\x1b[01;32m"
    #define COLOR_BRIGHT_YELLOW   "\x1b[01;33m"
    #define COLOR_BRIGHT_BLUE     "\x1b[01;34m"
    #define COLOR_BRIGHT_MAGENTA  "\x1b[01;35m"
    #define COLOR_BRIGHT_CYAN     "\x1b[01;36m"
    #define COLOR_BRIGHT_WHITE    "\x1b[01;37m"
    typedef const char *ccolor_t;
#endif

/* Initializes/finalizes output module (guaranteed to succeed) */
void output_module_initialize(void);
void output_module_finalize(void);

/* Opens normal/error output (guaranteed to succeed) */
void output_open(bool error_output);

/* Closes normal/error output (guaranteed to succeed) */
void output_close(bool error_output);

/* Writes message to normal/error output (guaranteed to succeed) */
void output_print(bool error_output, const cchar_t *format, ...) PRINTFLIKE(2, 3);
void output_print_color(bool error_output, ccolor_t color, const cchar_t *format, ...) PRINTFLIKE(3, 4);

/* Writes message to normal/error output (guaranteed to succeed) */
void output_vprint(bool error_output, const cchar_t *format, va_list va) PRINTFLIKE(2, 0);
void output_vprint_color(bool error_output, ccolor_t color, const cchar_t *format, va_list va) PRINTFLIKE(3, 0);

/* Write timestamp to normal/error output (guaranteed to succeed) */
void output_print_time(bool error_output);

#endif
