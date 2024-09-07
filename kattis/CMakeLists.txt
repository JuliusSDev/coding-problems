# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(CompileSubdirectories C)

# Set warnings as errors for GCC, Clang, and MSVC
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Werror)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
endif()

# Enable cppcheck and clang-tidy
set(CMAKE_CXX_CPPCHECK "cppcheck;--enable=all")
set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=*")

# Get a list of all subdirectories in the current directory (assuming each subdirectory is a project)
file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*)

# Set the output directory for the object files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Loop through each subdirectory
foreach(SUBDIR ${SUBDIRS})
    # Check if the subdirectory contains C source files
    file(GLOB_RECURSE C_FILES "${CMAKE_SOURCE_DIR}/${SUBDIR}/*.c")
    
    # If .c files are found in the subdirectory, treat it as a project
    if(C_FILES)
        # Create an executable for each subdirectory
        add_executable(${SUBDIR}_exec ${C_FILES})

        # Set the output directory for this executable
        set_target_properties(${SUBDIR}_exec PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
    endif()
endforeach()
