#ifndef COMMONLIB_ERROR_H
#define COMMONLIB_ERROR_H

#include "bool.h"
#include "char.h"
#include "macro.h"

/*#define ERROR_EMBED_ARGUMENTS*/ /* Store file and line as a part of the message (increases file size) */
#define ERROR_INCLUDE_EXPRESSION /* Include boolean expression in the trace */

#ifdef ERROR_EMBED_ARGUMENTS
    #define ERROR_FORMAT() COMMON_L(__RELATIVE_FILE__) COMMON_L(":") COMMON_L(__STRING_LINE__) COMMON_L(": Error")
    #define ERROR_FORMAT_F(FORMAT) COMMON_L(__RELATIVE_FILE__) COMMON_L(":") COMMON_L(__STRING_LINE__) COMMON_L(": Message: ") COMMON_L(FORMAT)
    #ifdef ERROR_INCLUDE_EXPRESSION
        #define ERROR_FORMAT_E(EXPRESSION) COMMON_L(__RELATIVE_FILE__) COMMON_L(":") COMMON_L(__STRING_LINE__) COMMON_L(": Condition `") COMMON_L(EXPRESSION) COMMON_L("' failed")
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) COMMON_L(__RELATIVE_FILE__) COMMON_L(":") COMMON_L(__STRING_LINE__) COMMON_L(": Condition `") COMMON_L(EXPRESSION) COMMON_L("' failed. Message: ") COMMON_L(FORMAT)
    #else
        #define ERROR_FORMAT_E(EXPRESSION) ERROR_FORMAT()
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) ERROR_FORMAT_F(FORMAT)
    #endif
#else
    #define ERROR_FORMAT() COMMON_S COMMON_L(":%d: Error"), COMMON_L(__RELATIVE_FILE__), __LINE__
    #define ERROR_FORMAT_F(FORMAT) COMMON_S COMMON_L(":%d: Message: ") COMMON_L(FORMAT), COMMON_L(__RELATIVE_FILE__), __LINE__
    #ifdef ERROR_INCLUDE_EXPRESSION
        #define ERROR_FORMAT_E(EXPRESSION) COMMON_S COMMON_L(":%d: Condition `") COMMON_S COMMON_L("' failed"), COMMON_L(__RELATIVE_FILE__), __LINE__, COMMON_L(EXPRESSION)
        #define ERROR_FORMAT_EF(EXPRESSION, FORMAT) COMMON_S COMMON_L(":%d: Condition `") COMMON_S COMMON_L("' failed. Message: ") COMMON_L(FORMAT), COMMON_L(__RELATIVE_FILE__), __LINE__, COMMON_L(EXPRESSION)
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
#define ERROR_RETURN_VERBATIM() return
#define ERROR_RETURN_OK() return

/* Assigns 'error' variable and goes to 'failure' label (GOTO = goto) */
#define GOTO() { error_internal_print_die(ERROR_FORMAT()); }
#define GOTO0(FORMAT) { error_internal_print_die(ERROR_FORMAT_F(FORMAT)); }
#define GOTO1(FORMAT, A) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define GOTO2(FORMAT, A, B) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define GOTO3(FORMAT, A, B, C) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Assigns 'error' variable and goes to 'failure' label if expression is false (AGOTO = assert goto) */
#define AGOTO(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT()); }
#define AGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT)); }
#define AGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define AGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define AGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Assigns 'error' variable and goes to 'failure' label if expression is error (PGOTO = propagate goto) */
#define PGOTO(EXPRESSION) { EXPRESSION; }
#define PGOTO0(EXPRESSION, FORMAT) { EXPRESSION; }
#define PGOTO1(EXPRESSION, FORMAT, A) { EXPRESSION; }
#define PGOTO2(EXPRESSION, FORMAT, A, B) { EXPRESSION; }
#define PGOTO3(EXPRESSION, FORMAT, A, B, C) { EXPRESSION; }

/* Returns the error (RET = return) */
#define RET() { error_internal_print_die(ERROR_FORMAT()); }
#define RET0(FORMAT) { error_internal_print_die(ERROR_FORMAT_F(FORMAT)); }
#define RET1(FORMAT, A) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define RET2(FORMAT, A, B) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define RET3(FORMAT, A, B, C) { error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is false (ARET = assert return) */
#define ARET(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT()); }
#define ARET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT)); }
#define ARET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A); }
#define ARET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B); }
#define ARET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else error_internal_print_die(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is error (PRET = propagate return) */
#define PRET(EXPRESSION) { EXPRESSION; }
#define PRET0(EXPRESSION, FORMAT) { EXPRESSION; }
#define PRET1(EXPRESSION, FORMAT, A) { EXPRESSION; }
#define PRET2(EXPRESSION, FORMAT, A, B) { EXPRESSION; }
#define PRET3(EXPRESSION, FORMAT, A, B, C) { EXPRESSION; }

/* Ignores the result of expression when it is guaranteed to succeed (PIGNORE = propagate ignore) */
#define PIGNORE(EXPRESSION) { EXPRESSION; }

/* Prints error and dies */
void error_internal_print_die(const cchar_t *format, ...) NORETURN PRINTFLIKE(1, 2);

#endif /* #ifdef ERROR_DIE */

#ifdef ERROR_PRINT

/* Essential macros */
#define ERROR_TYPE bool
#define ERROR_DECLARE() bool success
#define ERROR_ASSIGN(EXPRESSION) success = EXPRESSION
#define ERROR_RETURN() return success
#define ERROR_RETURN_VERBATIM() return success
#define ERROR_RETURN_OK() return true

/* Assigns 'error' variable and goes to 'failure' label (GOTO = goto) */
#define GOTO() { error_internal_print(ERROR_FORMAT()); success = false; goto failure; }
#define GOTO0(FORMAT) { error_internal_print(ERROR_FORMAT_F(FORMAT)); success = false; goto failure; }
#define GOTO1(FORMAT, A) { error_internal_print(ERROR_FORMAT_F(FORMAT), A); success = false; goto failure; }
#define GOTO2(FORMAT, A, B) { error_internal_print(ERROR_FORMAT_F(FORMAT), A, B); success = false; goto failure; }
#define GOTO3(FORMAT, A, B, C) { error_internal_print(ERROR_FORMAT_F(FORMAT), A, B, C); success = false; goto failure; }

/* Assigns 'error' variable and goes to 'failure' label if expression is false (AGOTO = assert goto) */
#define AGOTO(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_E(#EXPRESSION)); success = false; goto failure; } }
#define AGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); success = false; goto failure; } }
#define AGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); success = false; goto failure; } }
#define AGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); success = false; goto failure; } }
#define AGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); success = false; goto failure; } }

/* Assigns 'error' variable and goes to 'failure' label if expression is error (PGOTO = propagate goto) */
#define PGOTO(EXPRESSION) AGOTO(EXPRESSION)
#define PGOTO0(EXPRESSION, FORMAT) AGOTO(EXPRESSION, FORMAT)
#define PGOTO1(EXPRESSION, FORMAT, A) AGOTO(EXPRESSION, FORMAT, A)
#define PGOTO2(EXPRESSION, FORMAT, A, B) AGOTO(EXPRESSION, FORMAT, A, B)
#define PGOTO3(EXPRESSION, FORMAT, A, B, C) AGOTO(EXPRESSION, FORMAT, A, B, C)

/* Returns the error (RET = return) */
#define RET() { error_internal_print(ERROR_FORMAT()); return false; }
#define RET0(FORMAT) { error_internal_print(ERROR_FORMAT_F(FORMAT)); return false; }
#define RET1(FORMAT, A) { error_internal_print(ERROR_FORMAT_F(FORMAT), A); return false; }
#define RET2(FORMAT, A, B) { error_internal_print(ERROR_FORMAT_F(FORMAT), A, B); return false; }
#define RET3(FORMAT, A, B, C) { error_internal_print(ERROR_FORMAT_F(FORMAT), A, B, C); return false; }

/* Returns error if expression is false (ARET = assert return) */
#define ARET(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_E(#EXPRESSION)); return false; } }
#define ARET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); return false; } }
#define ARET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); return false; } }
#define ARET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); return false; } }
#define ARET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else { error_internal_print(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); return false; } }

/* Returns error if expression is error (PRET = propagate return) */
#define PRET(EXPRESSION) ARET(EXPRESSION)
#define PRET0(EXPRESSION, FORMAT) ARET0(EXPRESSION)
#define PRET1(EXPRESSION, FORMAT, A) ARET1(EXPRESSION, FORMAT, A)
#define PRET2(EXPRESSION, FORMAT, A, B) ARET2(EXPRESSION, FORMAT, A, B)
#define PRET3(EXPRESSION, FORMAT, A, B, C) ARET3(EXPRESSION, FORMAT, A, B, C)

/* Ignores the result of expression when it is guaranteed to succeed (PIGNORE = propagate ignore) */
#define PIGNORE(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else {} }

/* Prints error */
void error_internal_print(const cchar_t *format, ...) PRINTFLIKE(1, 2);

/* Ends error printing */
void error_print_close(void);

#endif /* #ifdef ERROR_PRINT */

#ifdef ERROR_TRACE

struct Error;
#define OK ((struct Error*)0)
#define PANIC ((struct Error*)1)

/* Essential macros */
#define ERROR_TYPE struct Error*
#define ERROR_DECLARE() struct Error *error
#define ERROR_ASSIGN(EXPRESSION) error = EXPRESSION
#define ERROR_RETURN() return error
#define ERROR_RETURN_VERBATIM() return error
#define ERROR_RETURN_OK() return OK

/* Assigns 'error' variable and goes to 'failure' label (GOTO = goto) */
#define GOTO() { error = error_internal_allocate(ERROR_FORMAT()); goto failure; }
#define GOTO0(FORMAT) { error = error_internal_allocate(ERROR_FORMAT_F(FORMAT)); goto failure; }
#define GOTO1(FORMAT, A) { error = error_internal_allocate(ERROR_FORMAT_F(FORMAT), A); goto failure; }
#define GOTO2(FORMAT, A, B) { error = error_internal_allocate(ERROR_FORMAT_F(FORMAT), A, B); goto failure; }
#define GOTO3(FORMAT, A, B, C) { error = error_internal_allocate(ERROR_FORMAT_F(FORMAT), A, B, C); goto failure; }

/* Assigns 'error' variable and goes to 'failure' label if expression is false (AGOTO = assert goto) */
#define AGOTO(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else { error = error_internal_allocate(ERROR_FORMAT_E(#EXPRESSION)); goto failure; } }
#define AGOTO0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else { error = error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); goto failure; } }
#define AGOTO1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else { error = error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); goto failure; } }
#define AGOTO2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else { error = error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); goto failure; } }
#define AGOTO3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else { error = error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); goto failure; } }

/* Assigns 'error' variable and goes to 'failure' label if expression is error (PGOTO = propagate goto) */
#define PGOTO(EXPRESSION) { struct Error *check = EXPRESSION; if (check != OK) { error = error_internal_allocate_append(check, ERROR_FORMAT_E(#EXPRESSION)); goto failure; } }
#define PGOTO0(EXPRESSION, FORMAT) { struct Error *check = EXPRESSION; if (check != OK) { error = error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); goto failure; } }
#define PGOTO1(EXPRESSION, FORMAT, A) { struct Error *check = EXPRESSION; if (check != OK) { error = error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); goto failure; } }
#define PGOTO2(EXPRESSION, FORMAT, A, B) { struct Error *check = EXPRESSION; if (check != OK) { error = error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); goto failure; } }
#define PGOTO3(EXPRESSION, FORMAT, A, B, C) { struct Error *check = EXPRESSION; if (check != OK) { error = error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); goto failure; } }

/* Returns the error (RET = return) */
#define RET() { return error_internal_allocate(ERROR_FORMAT()); }
#define RET0(FORMAT) { return error_internal_allocate(ERROR_FORMAT_F(FORMAT)); }
#define RET1(FORMAT, A) { return error_internal_allocate(ERROR_FORMAT_F(FORMAT), A); }
#define RET2(FORMAT, A, B) { return error_internal_allocate(ERROR_FORMAT_F(FORMAT), A, B); }
#define RET3(FORMAT, A, B, C) { return error_internal_allocate(ERROR_FORMAT_F(FORMAT), A, B, C); }

/* Returns error if expression is false (ARET = assert return) */
#define ARET(EXPRESSION) { const bool check = EXPRESSION; if (check) {} else return error_internal_allocate(ERROR_FORMAT_E(#EXPRESSION)); }
#define ARET0(EXPRESSION, FORMAT) { const bool check = EXPRESSION; if (check) {} else return error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); }
#define ARET1(EXPRESSION, FORMAT, A) { const bool check = EXPRESSION; if (check) {} else return error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); }
#define ARET2(EXPRESSION, FORMAT, A, B) { const bool check = EXPRESSION; if (check) {} else return error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); }
#define ARET3(EXPRESSION, FORMAT, A, B, C) { const bool check = EXPRESSION; if (check) {} else return error_internal_allocate(ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); }

/* Returns error if expression is error (PRET = propagate return) */
#define PRET(EXPRESSION) { struct Error *check = EXPRESSION; if (check != OK) return error_internal_allocate_append(check, ERROR_FORMAT_E(#EXPRESSION)); }
#define PRET0(EXPRESSION, FORMAT) { struct Error *check = EXPRESSION; if (check != OK) return error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT)); }
#define PRET1(EXPRESSION, FORMAT, A) { struct Error *check = EXPRESSION; if (check != OK) return error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A); }
#define PRET2(EXPRESSION, FORMAT, A, B) { struct Error *check = EXPRESSION; if (check != OK) return error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B); }
#define PRET3(EXPRESSION, FORMAT, A, B, C) { struct Error *check = EXPRESSION; if (check != OK) return error_internal_allocate_append(check, ERROR_FORMAT_EF(#EXPRESSION, FORMAT), A, B, C); }

/* Ignores the result of expression when it is guaranteed to succeed (PIGNORE = propagate ignore) */
#define PIGNORE(EXPRESSION) { struct Error *check = EXPRESSION; if (check != OK) {} else {} }

/* Creates error (guaranteed to succeed) */
struct Error *error_internal_allocate(const cchar_t *format, ...) NODISCARD PRINTFLIKE(1, 2);

/* Appends error to an existing error (guaranteed to succeed) */
struct Error *error_internal_allocate_append(struct Error *error, const cchar_t *format, ...) NODISCARD PRINTFLIKE(2, 3);

/* Gets error code to be returned by application (guaranteed to succeed) */
int error_get_exit_code(const struct Error *error);

/* Prints error (guaranteed to succeed) */
void error_print(const struct Error *error);

/* Finalizes error (guaranteed to succeed) */
void error_finalize(struct Error *error);

#endif /* #ifdef ERROR_TRACE */

#endif
