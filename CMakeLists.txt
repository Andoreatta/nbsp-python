cmake_minimum_required(VERSION 3.20...3.26)

project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

set(pybind11_DIR $ENV{Path}/Lib/site-packages/pybind11/share/cmake/pybind11)
link_directories("C:/Program Files (x86)/NITGEN/eNBSP SDK Professional/SDK/lib/x64")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

python_add_library(_core MODULE src/main.cpp WITH_SOABI)
add_compile_options(-pedantic-errors -Wall -Weffc++ -Wextra  -Wconversion -Wsign-conversion -Werror) # Cmake "translates" the flags depending on the compiler (-W4 for MSVC, -Wall for GCC, etc.)
target_link_libraries(_core PRIVATE pybind11::headers pybind11::module NBioBSP)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _core DESTINATION nbsp_python)
