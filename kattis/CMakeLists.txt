cmake_minimum_required(VERSION 3.10)

project(my_project)

# Collect all .c files recursively in subdirectories
file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS "*.c")

# Exclude directories if needed
list(FILTER C_SOURCES EXCLUDE REGEX "path/to/exclude")

# Set compiler warnings and flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# clang-tidy checks (disabling restrictive system libc check)
set(CMAKE_C_CLANG_TIDY "clang-tidy-12;-checks=*,-llvmlibc-restrict-system-libc-headers;-warnings-as-errors=*")

# clang-format check (dry run)
add_custom_target(check-format ALL
    COMMENT "Running clang-format check on all C source files"
)

foreach(cfile ${C_SOURCES})
    # Get the file name without the directory path
    get_filename_component(cfile_name ${cfile} NAME)

    # Create a valid target name by using the file name without slashes
    set(target_name "${cfile_name}_format")

    add_custom_command(
        OUTPUT ${cfile}.format
        COMMAND clang-format -Werror -n -style='{BasedOnStyle: Google, IndentWidth: 4}' ${cfile}
        DEPENDS ${cfile}
        COMMENT "Checking format for ${cfile}"
    )

    add_custom_target(${target_name} DEPENDS ${cfile}.format)
    add_dependencies(check-format ${target_name})
endforeach()

# Add a custom target for running 'clang-format -i' to format all .c files
add_custom_target(format
    COMMAND clang-format -i -style='{BasedOnStyle: Google, IndentWidth: 4}' ${C_SOURCES}
    COMMENT "Formatting all C source files with clang-format"
)

# Add executables for each directory
foreach(cfile ${C_SOURCES})
    get_filename_component(exe_name ${cfile} NAME_WE)
    add_executable(${exe_name}_exec ${cfile})
    set_target_properties(${exe_name}_exec PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endforeach()
