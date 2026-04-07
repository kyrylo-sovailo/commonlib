#include "../include/error.h"
#include "../include/output.h"
#include "../include/path.h"

#include <stdio.h>

ERROR_TYPE test1(void) NODISCARD;
ERROR_TYPE test2(void) NODISCARD;
ERROR_TYPE test3(int argc, char **argv) NODISCARD;

ERROR_TYPE test1(void)
{
    RET0("Hello error handling");
}

ERROR_TYPE test2(void)
{
    PRET(test1());
    ERROR_RETURN_OK();
}

ERROR_TYPE test3(int argc, char **argv)
{
    ERROR_DECLARE();
    PGOTO(path_module_initialize(argc, argv));
    PGOTO(test2());
    path_module_finalize();
    ERROR_RETURN_OK();

    #ifndef ERROR_DIE
        failure:
        path_module_finalize();
        ERROR_RETURN();
    #endif
}

int main(int argc, char **argv)
{
    #if defined(ERROR_DIE)
        int code = 0;
    #elif defined(ERROR_PRINT)
        int code = 0;
        bool success;
    #else
        int code = 0;
        struct Error *error;
    #endif

    output_module_initialize();
    #if defined(ERROR_DIE)
        test3(argc, argv);
    #elif defined(ERROR_PRINT)
        success = test3(argc, argv);
        if (!success)
        {
            error_print_close();
            printf("User received an error!\n");
            code = 1;
        }
    #else
        error = test3(argc, argv);
        if (error != OK)
        {
            error_print(error);
            printf("User received an error!\n");
            code = error_get_exit_code(error);
            error_finalize(error);
        }
    #endif
    output_module_finalize();

    return code;
}
