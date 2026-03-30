cmake_minimum_required(VERSION 3.10)
project(CommonLib LANGUAGES C CXX)

# Compiler identification
set(COMPILER "${CMAKE_C_COMPILER_ID}")
if("${COMPILER}" STREQUAL "MSVC")
    set(COMPILER_STYLE "MSVC")
elseif("${COMPILER}" STREQUAL "GNU" OR "${COMPILER}" STREQUAL "AppleClang")
    set(COMPILER_STYLE "GNU")
elseif("${COMPILER}" STREQUAL "Clang")
    if ("${CMAKE_C_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
        set(COMPILER_STYLE "MSVC")
    else()
        set(COMPILER_STYLE "GNU")
    endif()
endif()

# Compiler options
if("${COMPILER_STYLE}" STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic)
    add_compile_options(-Wconversion -Wsign-conversion -Wmissing-declarations -Wstrict-prototypes -Wunreachable-code)
    add_compile_options(-Werror)
    if("${COMPILER}" STREQUAL "GNU")
        add_compile_options(-fanalyzer)
    endif()
    add_link_options(-Wl,--no-undefined)
elseif("${COMPILER_STYLE}" STREQUAL "MSVC")
    add_compile_options(/Wall)
    add_compile_options(/wd4668) #C4668: Macro is not defined as a preprocessor macro
    add_compile_options(/wd4625) #C4625: Copy constructor was implicitly defined as deleted
    add_compile_options(/wd4626) #C4626: Assignment operator was implicitly defined as deleted
    add_compile_options(/wd4710) #C4710: Function not inlined
    add_compile_options(/wd4711) #C4711: Selected for automatic inline expansion
    add_compile_options(/wd4820) #C4820: N bytes padding added after data member
    add_compile_options(/wd4868) #C4868: Compiler may not enforce left-to-right evaluation order in braced initializer list
    add_compile_options(/wd5039) #C5039: Pointer or reference to potentially throwing function passed to 'extern "C"
    add_compile_options(/wd5045) #C5045: Compiler will insert Spectre mitigation for memory
endif()

# Source files
set(SOURCES
source/char_buffer.c
source/char_hmap.c
source/error.c
source/generic_buffer_implementation.c
source/generic_hash_map_implementation.c
source/http.c
source/main.c
source/output.c
source/path.c
source/ring.c
source/string.c)

foreach(SOURCE IN LISTS SOURCES)
    get_filename_component(CXX_SOURCE "${SOURCE}" NAME_WE)
    set(CXX_SOURCE "${CMAKE_BINARY_DIR}/${CXX_SOURCE}.cpp")
    file(RELATIVE_PATH CXX_SOURCE "${CMAKE_SOURCE_DIR}" "${CXX_SOURCE}")
    add_custom_command(
        OUTPUT "${CMAKE_SOURCE_DIR}/${CXX_SOURCE}"
        DEPENDS "${CMAKE_SOURCE_DIR}/${SOURCE}"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${SOURCE}" "${CMAKE_SOURCE_DIR}/${CXX_SOURCE}"
        COMMENT "Generating ${CXX_SOURCE}")
    list(APPEND CXX_SOURCES "${CXX_SOURCE}")
endforeach()

# Custom add_executable / add_library
function(add_executable_relative TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    math(EXPR ARGC_WITHOUT_RESERVED "${ARGC} - 1")
    set(OPTIONS WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL)
    foreach(I RANGE 1 ${ARGC_WITHOUT_RESERVED} 1)
        if (NOT "${ARGV${I}}" IN_LIST OPTIONS)
            set(FILE "${ARGV${I}}")
            if(IS_ABSOLUTE "${FILE}")
                file(RELATIVE_PATH RELATIVE_FILE "${CMAKE_SOURCE_DIR}" "${FILE}")
            else()
                set(RELATIVE_PATH "${FILE}")
            endif()
            get_filename_component(BASENAME_FILE "${FILE}" NAME)
            set_source_files_properties("${FILE}" PROPERTIES COMPILE_DEFINITIONS "__RELATIVE_FILE__=\"${RELATIVE_FILE}\"")
            set_source_files_properties("${FILE}" PROPERTIES COMPILE_DEFINITIONS "__BASENAME_FILE__=\"${BASENAME_FILE}\"")
        endif()
    endforeach()
endfunction()

function(add_library_relative TARGET_NAME FORCE_CXX)
    add_library(${TARGET_NAME} ${ARGN})
    math(EXPR ARGC_WITHOUT_RESERVED "${ARGC} - 1")
    set(OPTIONS WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL)
    foreach(I RANGE 1 ${ARGC_WITHOUT_RESERVED} 1)
        if (NOT "${ARGV${I}}" IN_LIST OPTIONS)
            set(FILE "${ARGV${I}}")
            if(IS_ABSOLUTE "${FILE}")
                file(RELATIVE_PATH RELATIVE_FILE "${CMAKE_SOURCE_DIR}" "${FILE}")
            else()
                set(RELATIVE_PATH "${FILE}")
            endif()
            get_filename_component(BASENAME_FILE "${FILE}" NAME)
            set_source_files_properties("${FILE}" PROPERTIES COMPILE_DEFINITIONS "__RELATIVE_FILE__=\"${RELATIVE_FILE}\"")
            set_source_files_properties("${FILE}" PROPERTIES COMPILE_DEFINITIONS "__BASENAME_FILE__=\"${BASENAME_FILE}\"")
        endif()
    endforeach()
endfunction()

# Define all standards and all styles
if("${COMPILER_STYLE}" STREQUAL "GNU")
    set(STANDARDS c89;c99;c23;c++98)
else()
    set(STANDARDS c)
endif()
set(STYLES ERROR_DIE;ERROR_PRINT;ERROR_TRACE)

# Compile all
foreach(STANDARD IN LISTS STANDARDS)
    foreach(STYLE IN LISTS STYLES)
        string(SUBSTRING "${STYLE}" 6 1 STYLE_SUFFIX)
        string(TOLOWER "${STYLE_SUFFIX}" STYLE_SUFFIX)
        if("${COMPILER_STYLE}" STREQUAL "GNU")
            set(TARGET common_${STANDARD}${STYLE_SUFFIX})
            if(${STANDARD} MATCHES "^c\\+\\+")
                set(FORCE_CXX TRUE)
            else()
                set(FORCE_CXX FALSE)
            endif()
        else()
            set(TARGET common_${STYLE_SUFFIX})
            set(FORCE_CXX FALSE)
        endif()
        
        if(FORCE_CXX)
            add_executable_relative(${TARGET} ${CXX_SOURCES})
            target_compile_options(${TARGET} PRIVATE -Wno-error) #Seems to be a bug
        else()
            add_executable_relative(${TARGET} ${SOURCES})
        endif()
        
        if("${COMPILER_STYLE}" STREQUAL "GNU")
            target_compile_options(${TARGET} PRIVATE -std=${STANDARD})
        endif()
        target_compile_definitions(${TARGET} PRIVATE ${STYLE})
    endforeach()
endforeach()
