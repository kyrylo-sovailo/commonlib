#ifndef ERROR_H
#define ERROR_H

#include "bool.h"
#include "macro.h"

/*#define ERROR_EMBED_ARGUMENTS*/ /* Store file and line as a part of the message (increases file size) */
#define ERROR_INCLUDE_EXPRESSION /* Include boolean expression in the trace */

#ifdef ERROR_EMBED_ARGUMENTS
    #define ERROR_FORMAT() __RELATIVE_FILE__ ":" ERROR_STRINGIZE_LINE ": Error"
    #define ERROR_FORMAT_F(FORMAT) __RELATIVE_FILE__ ":" ERROR_STRINGIZE_LINE ": Message: " FORMAT
    #ifdef ERROR_INCLUDE_EXPRESSION
        #define ERROR_FORMAT_E(EXPRESSION) __RELATIVE_FILE__ ":" ERROR_STRINGIZE_LINE ": Condition `" EXPRESSION "' failed"
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) __RELATIVE_FILE__ ":" ERROR_STRINGIZE_LINE ": Condition `" EXPRESSION "' failed. Message: " FORMAT
    #else
        #define ERROR_FORMAT_E(EXPRESSION) ERROR_FORMAT()
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) ERROR_FORMAT_F(FORMAT)
    #endif
#else
    #define ERROR_FORMAT() "%s:%d: Error", __RELATIVE_FILE__, __LINE__
    #define ERROR_FORMAT_F(FORMAT) "%s:%d: Message: " FORMAT, __RELATIVE_FILE__, __LINE__
    #ifdef ERROR_INCLUDE_EXPRESSION
        #define ERROR_FORMAT_E(EXPRESSION) "%s:%d: Condition `%s' failed", __RELATIVE_FILE__, __LINE__, EXPRESSION
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) "%s:%d: Condition `%s' failed. Message: " FORMAT, __RELATIVE_FILE__, __LINE__, EXPRESSION
    #else
        #define ERROR_FORMAT_E(EXPRESSION) ERROR_FORMAT()
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) ERROR_FORMAT_F(FORMAT)
    #endif
#endif

#ifdef ERROR_DIE

/* Essential macros */
#define ERROR_TYPE void
#define ERROR_DECLARE()
#define ERROR_ASSIGN(EXPRESSION) EXPRESSION
#define ERROR_RETURN() return
#define ERROR_RETURN_OK() return

/* Assigns 'error' variable and goes to 'finalize' label (GOTO = goto) */
#define GOTO() { error_print_die(ERROR_FORMAT()); }
#define GOTO0(FORMAT) { error_print_die(ERROR_FORMAT_F(FORMAT)); }
#define GOTO1(FORMAT, A) { error_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define GOTO2(FORMAT, A, B) { error_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define GOTO3(FORMAT, A, B, C) { error_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Assigns 'error' variable and goes to 'finalize' label if expression is false (CGOTO = conditional goto) */
#define CGOTO(EXPRESSION) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT()); }
#define CGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT)); }
#define CGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define CGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define CGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Assigns 'error' variable and goes to 'finalize' label if expression is error (EGOTO = error goto) */
#define EGOTO(EXPRESSION) { EXPRESSION; }
#define EGOTO0(EXPRESSION, FORMAT) { EXPRESSION; }
#define EGOTO1(EXPRESSION, FORMAT, A) { EXPRESSION; }
#define EGOTO2(EXPRESSION, FORMAT, A, B) { EXPRESSION; }
#define EGOTO3(EXPRESSION, FORMAT, A, B, C) { EXPRESSION; }

/* Returns the error (RET = return) */
#define RET() { error_print_die(ERROR_FORMAT()); }
#define RET0(FORMAT) { error_print_die(ERROR_FORMAT_F(FORMAT)); }
#define RET1(FORMAT, A) { error_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define RET2(FORMAT, A, B) { error_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define RET3(FORMAT, A, B, C) { error_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is false (CRET = conditional return) */
#define CRET(EXPRESSION) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT()); }
#define CRET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT)); }
#define CRET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define CRET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define CRET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) error_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is error (ERET = error return) */
#define ERET(EXPRESSION) { EXPRESSION; }
#define ERET0(EXPRESSION, FORMAT) { EXPRESSION; }
#define ERET1(EXPRESSION, FORMAT, A) { EXPRESSION; }
#define ERET2(EXPRESSION, FORMAT, A, B) { EXPRESSION; }
#define ERET3(EXPRESSION, FORMAT, A, B, C) { EXPRESSION; }

/* Returns either error or success (PRET = propagate return) */
#define PRET(EXPRESSION) { EXPRESSION; }
#define PRET0(EXPRESSION, FORMAT) { EXPRESSION; }
#define PRET1(EXPRESSION, FORMAT, A) { EXPRESSION; }
#define PRET2(EXPRESSION, FORMAT, A, B) { EXPRESSION; }
#define PRET3(EXPRESSION, FORMAT, A, B, C) { EXPRESSION; }

/* Prints error */
void error_print_die(const char *format, ...) NORETURN PRINTFLIKE(1, 2);

#endif /* #ifdef ERROR_DIE */

#ifdef ERROR_PRINT

/* Essential macros */
#define ERROR_TYPE bool
#define ERROR_DECLARE() bool success
#define ERROR_ASSIGN(EXPRESSION) success = EXPRESSION
#define ERROR_RETURN() return success
#define ERROR_RETURN_OK() return true

/* Assigns 'error' variable and goes to 'finalize' label (GOTO = goto) */
#define GOTO() { error_print(ERROR_FORMAT()); success = false; goto finalize; }
#define GOTO0(FORMAT) { error_print(ERROR_FORMAT_F(FORMAT)); success = false; goto finalize; }
#define GOTO1(FORMAT, A) { error_print(ERROR_FORMAT_F(FORMAT), A); success = false; goto finalize; }
#define GOTO2(FORMAT, A, B) { error_print(ERROR_FORMAT_F(FORMAT), A, B); success = false; goto finalize; }
#define GOTO3(FORMAT, A, B, C) { error_print(ERROR_FORMAT_F(FORMAT), A, B, C); success = false; goto finalize; }

/* Assigns 'error' variable and goes to 'finalize' label if expression is false (CGOTO = conditional goto) */
#define CGOTO(EXPRESSION) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_E(#EXPRESSION)); success = false; goto finalize; } }
#define CGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); success = false; goto finalize; } }
#define CGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); success = false; goto finalize; } }
#define CGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); success = false; goto finalize; } }
#define CGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); success = false; goto finalize; } }

/* Assigns 'error' variable and goes to 'finalize' label if expression is error (EGOTO = error goto) */
#define EGOTO(EXPRESSION) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_E(#EXPRESSION)); success = false; goto finalize; } }
#define EGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); success = false; goto finalize; } }
#define EGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); success = false; goto finalize; } }
#define EGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); success = false; goto finalize; } }
#define EGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); success = false; goto finalize; } }

/* Returns the error (RET = return) */
#define RET() { error_print(ERROR_FORMAT()); return false; }
#define RET0(FORMAT) { error_print(ERROR_FORMAT_F(FORMAT)); return false; }
#define RET1(FORMAT, A) { error_print(ERROR_FORMAT_F(FORMAT), A); return false; }
#define RET2(FORMAT, A, B) { error_print(ERROR_FORMAT_F(FORMAT), A, B); return false; }
#define RET3(FORMAT, A, B, C) { error_print(ERROR_FORMAT_F(FORMAT), A, B, C); return false; }

/* Returns error if expression is false (CRET = conditional return) */
#define CRET(EXPRESSION) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_E(#EXPRESSION)); return false; } }
#define CRET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); return false; } }
#define CRET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); return false; } }
#define CRET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); return false; } }
#define CRET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); return false; } }

/* Returns error if expression is error (ERET = error return) */
#define ERET(EXPRESSION) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_E(#EXPRESSION)); return false; } }
#define ERET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); return false; } }
#define ERET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); return false; } }
#define ERET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); return false; } }
#define ERET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) { error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); return false; } }

/* Returns either error or success (PRET = propagate return) */
#define PRET(EXPRESSION) { const bool check = EXPRESSION; if (!check) error_print(ERROR_FORMAT_E(#EXPRESSION)); return check; }
#define PRET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); return check; }
#define PRET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); return check; }
#define PRET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); return check; }
#define PRET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) error_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); return check; }

/* Prints error */
void error_print(const char *format, ...) PRINTFLIKE(1, 2);

#endif /* #ifdef ERROR_PRINT */

#ifdef ERROR_TRACE

struct Error;
#define OK ((struct Error*)0)
#define PANIC ((struct Error*)1)

/* Essential macros */
#define ERROR_TYPE struct Error*
#define ERROR_DECLARE() struct Error* error
#define ERROR_ASSIGN(EXPRESSION) error = EXPRESSION
#define ERROR_RETURN() return error
#define ERROR_RETURN_OK() return OK

/* Assigns 'error' variable and goes to 'finalize' label (GOTO = goto) */
#define GOTO() { error = error_allocate(ERROR_FORMAT()); goto finalize; }
#define GOTO0(FORMAT) { error = error_allocate(ERROR_FORMAT_F(FORMAT)); goto finalize; }
#define GOTO1(FORMAT, A) { error = error_allocate(ERROR_FORMAT_F(FORMAT), A); goto finalize; }
#define GOTO2(FORMAT, A, B) { error = error_allocate(ERROR_FORMAT_F(FORMAT), A, B); goto finalize; }
#define GOTO3(FORMAT, A, B, C) { error = error_allocate(ERROR_FORMAT_F(FORMAT), A, B, C); goto finalize; }

/* Assigns 'error' variable and goes to 'finalize' label if expression is false (CGOTO = conditional goto) */
#define CGOTO(EXPRESSION) { const bool check = EXPRESSION; if (!check) { error = error_allocate(ERROR_FORMAT_E(#EXPRESSION)); goto finalize; } }
#define CGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) { error = error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); goto finalize; } }
#define CGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) { error = error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); goto finalize; } }
#define CGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) { error = error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); goto finalize; } }
#define CGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) { error = error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); goto finalize; } }

/* Assigns 'error' variable and goes to 'finalize' label if expression is error (EGOTO = error goto) */
#define EGOTO(EXPRESSION) { struct Error *check = EXPRESSION; if (check != OK) { error = error_allocate_append(check, ERROR_FORMAT_E(#EXPRESSION)); goto finalize; } }
#define EGOTO0(EXPRESSION, FORMAT) { struct Error *check = EXPRESSION; if (check != OK) { error = error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); goto finalize; } }
#define EGOTO1(EXPRESSION, FORMAT, A) { struct Error *check = EXPRESSION; if (check != OK) { error = error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); goto finalize; } }
#define EGOTO2(EXPRESSION, FORMAT, A, B) { struct Error *check = EXPRESSION; if (check != OK) { error = error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); goto finalize; } }
#define EGOTO3(EXPRESSION, FORMAT, A, B, C) { struct Error *check = EXPRESSION; if (check != OK) { error = error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); goto finalize; } }

/* Returns the error (RET = return) */
#define RET() { return error_allocate(ERROR_FORMAT()); }
#define RET0(FORMAT) { return error_allocate(ERROR_FORMAT_F(FORMAT)); }
#define RET1(FORMAT, A) { return error_allocate(ERROR_FORMAT_F(FORMAT), A); }
#define RET2(FORMAT, A, B) { return error_allocate(ERROR_FORMAT_F(FORMAT), A, B); }
#define RET3(FORMAT, A, B, C) { return error_allocate(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is false (CRET = conditional return) */
#define CRET(EXPRESSION) { const bool check = EXPRESSION; if (!check) return error_allocate(ERROR_FORMAT_E(#EXPRESSION)); }
#define CRET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (!check) return error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); }
#define CRET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (!check) return error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); }
#define CRET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (!check) return error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); }
#define CRET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (!check) return error_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); }

/* Returns error if expression is error (ERET = error return) */
#define ERET(EXPRESSION) { struct Error *check = EXPRESSION; if (check != OK) return error_allocate_append(check, ERROR_FORMAT_E(#EXPRESSION)); }
#define ERET0(EXPRESSION, FORMAT) { struct Error *check = EXPRESSION; if (check != OK) return error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); }
#define ERET1(EXPRESSION, FORMAT, A) { struct Error *check = EXPRESSION; if (check != OK) return error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); }
#define ERET2(EXPRESSION, FORMAT, A, B) { struct Error *check = EXPRESSION; if (check != OK) return error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); }
#define ERET3(EXPRESSION, FORMAT, A, B, C) { struct Error *check = EXPRESSION; if (check != OK) return error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); }

/* Returns either error or success (PRET = propagate return) */
#define PRET(EXPRESSION) { struct Error *check = EXPRESSION; return (check != OK) ? error_allocate_append(check, ERROR_FORMAT_E(#EXPRESSION)) : OK; }
#define PRET0(EXPRESSION, FORMAT) { struct Error *check = EXPRESSION; return (check != OK) ? error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT)) : OK; }
#define PRET1(EXPRESSION, FORMAT, A) { struct Error *check = EXPRESSION; return (check != OK) ? error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A) : OK; }
#define PRET2(EXPRESSION, FORMAT, A, B) { struct Error *check = EXPRESSION; return (check != OK) ? error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B) : OK; }
#define PRET3(EXPRESSION, FORMAT, A, B, C) { struct Error *check = EXPRESSION; return (check != OK) ? error_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C) : OK; }

/* Creates error (guaranteed to succeed) */
struct Error *error_allocate(const char *format, ...) NODISCARD PRINTFLIKE(1, 2);

/* Appends error to an existing error (guaranteed to succeed) */
struct Error *error_allocate_append(struct Error *error, const char *format, ...) NODISCARD PRINTFLIKE(2, 3);

/* Gets error code to be returned by application (guaranteed to succeed) */
int error_get_exit_code(const struct Error *error);

/* Prints error (guaranteed to succeed) */
void error_print(const struct Error *error);

/* Finalizes error (guaranteed to succeed) */
void error_finalize(struct Error *error);

#endif /* #ifdef ERROR_TRACE */

#endif
