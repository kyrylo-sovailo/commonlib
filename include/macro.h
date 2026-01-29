#ifndef MACRO_H
#define MACRO_H

/* Default error handling */
#ifndef ERROR_DIE
    #ifndef ERROR_PRINT
        #ifndef ERROR_TRACE
            #define ERROR_TRACE
        #endif
    #endif
#endif

/* Function attributes */
#ifdef __GNUC__
    #define PRINTFLIKE(FORMAT_POSITION, DOTS_POSITION) __attribute__((format(printf, FORMAT_POSITION, DOTS_POSITION)))
    #ifdef ERROR_DIE
        #define NODISCARD
    #else
        #define NODISCARD __attribute__((warn_unused_result))
    #endif
    #define NORETURN __attribute__((noreturn))
#else
    #define PRINTFLIKE(FORMAT_POSITION, DOTS_POSITION)
    #define NODISCARD
    #define NORETURN
#endif

/* Restrict keyword */
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ < 199901L
        #define restrict
    #endif
#else
    #define restrict
#endif

/* Stringification */
#define STRINGIZE(A) STRINGIZE_INTERNAL(A)
#define STRINGIZE_INTERNAL(A) #A

/* File and line */
#ifndef __RELATIVE_FILE__
    #define __RELATIVE_FILE__ __FILE__
#endif
#ifndef __BASENAME_FILE__
    #define __BASENAME_FILE__ __FILE__
#endif
#define __STRING_LINE__ STRINGIZE(__LINE__)

#endif
