#include "../include/error.h"
#include "../include/output.h"
#include "../include/path.h"

#ifdef WIN32
    #include <Windows.h>
    #include <shellapi.h>
#endif

#include <stdio.h>

static ERROR_TYPE test1(void)
{
    RET0("Hello error handling");
}

static ERROR_TYPE test2(void)
{
    PRET(test1());
    ERROR_RETURN_OK();
}

static ERROR_TYPE test3(int argc, cchar_t **argv)
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

static int common_main(int argc, cchar_t **argv)
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

#if defined(WIN32) && defined(UNICODE)
int main(void)
{
    int code = 1;
    int argc;
    cchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv != NULL)
    {
        code = common_main(argc, argv);
        LocalFree(argv);
    }
    return code;
}
#else
int main(int argc, char **argv)
{
    return common_main(argc, argv);
}
#endif
