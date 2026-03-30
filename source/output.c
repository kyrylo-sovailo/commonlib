#include "../include/output.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

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

void output_print_time(void)
{
    time_t global_time;
    struct tm *p_global_calender, global_calender;
    struct tm *p_local_calender, local_calender;
    char calender_buffer[64];

    /* Print time */
    global_time = time(NULL);
    p_global_calender = gmtime(&global_time);
    if (p_global_calender != NULL) global_calender = *p_global_calender;
    p_local_calender = localtime(&global_time);
    if (p_local_calender != NULL) local_calender = *p_local_calender;
    if (p_global_calender != NULL)
    {
        strftime(calender_buffer, sizeof(calender_buffer), "%a, %d %b %Y %H:%M:%S %Z", &global_calender);
        output_print("%s\n", calender_buffer);
        if (p_local_calender != NULL)
        {
            strftime(calender_buffer, sizeof(calender_buffer), "%a, %d %b %Y %H:%M:%S %Z", &local_calender);
            output_print("%s\n", calender_buffer);
        }
    }
}
