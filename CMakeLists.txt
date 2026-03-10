cmake_minimum_required(VERSION 3.10)
project(CommonLib LANGUAGES C)
# All warnings
add_compile_options(-Wall -Wextra -pedantic)
# Even more warnings
add_compile_options(-Wconversion -Wsign-conversion -Wmissing-declarations -Wstrict-prototypes -Wunreachable-code)
# Even stricter warnings
add_compile_options(-Werror)
# Static analyzer
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fanalyzer)
endif()
# Ensure everything is implemented
add_link_options(-Wl,--no-undefined)

set(SOURCES
source/char_buffer.c
source/error.c
source/generic_buffer_implementation.c
source/generic_hash_map_implementation.c
source/http.c
source/main.c
source/output.c
source/path.c
source/ring.c
source/string.c)

function(add_executable_relative TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    math(EXPR ARGC_MINUS_ONE "${ARGC} - 1")
    set(OPTIONS WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL)
    foreach(I RANGE 1 ${ARGC_MINUS_ONE} 1)
        if (NOT "${ARGV${I}}" IN_LIST OPTIONS)
            set(RELATIVE_FILE "${ARGV${I}}")
            get_filename_component(BASENAME_FILE "${ARGV${I}}" NAME)
            set_source_files_properties("${RELATIVE_FILE}" PROPERTIES COMPILE_DEFINITIONS "__RELATIVE_FILE__=\"${RELATIVE_FILE}\"")
            set_source_files_properties("${RELATIVE_FILE}" PROPERTIES COMPILE_DEFINITIONS "__BASENAME_FILE__=\"${BASENAME_FILE}\"")
        endif()
    endforeach()
endfunction()

function(add_library_relative TARGET_NAME)
    add_library(${TARGET_NAME} ${ARGN})
    math(EXPR ARGC_MINUS_ONE "${ARGC} - 1")
    set(OPTIONS WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL)
    foreach(I RANGE 1 ${ARGC_MINUS_ONE} 1)
        if (NOT "${ARGV${I}}" IN_LIST OPTIONS)
            set(RELATIVE_FILE "${ARGV${I}}")
            get_filename_component(BASENAME_FILE "${ARGV${I}}" NAME)
            set_source_files_properties("${RELATIVE_FILE}" PROPERTIES COMPILE_DEFINITIONS "__RELATIVE_FILE__=\"${RELATIVE_FILE}\"")
            set_source_files_properties("${RELATIVE_FILE}" PROPERTIES COMPILE_DEFINITIONS "__BASENAME_FILE__=\"${BASENAME_FILE}\"")
        endif()
    endforeach()
endfunction()

foreach(STANDARD IN ITEMS c89 c99 c23)
    foreach(STYLE IN ITEMS ERROR_DIE ERROR_PRINT ERROR_TRACE)
        string(SUBSTRING "${STYLE}" 6 1 STYLE_SUFFIX)
        string(TOLOWER "${STYLE_SUFFIX}" STYLE_SUFFIX)
        set(TARGET common_${STANDARD}${STYLE_SUFFIX})
        add_executable_relative(${TARGET} ${SOURCES})
        target_compile_options(${TARGET} PRIVATE -ansi -std=${STANDARD})
        target_compile_definitions(${TARGET} PRIVATE ${STYLE})
    endforeach()
endforeach()