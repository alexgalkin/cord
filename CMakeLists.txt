cmake_minimum_required(VERSION 3.6)
project(f5-cord)

add_library(f5-cord INTERFACE)
target_include_directories(f5-cord INTERFACE include)
if(CMAKE_VERSION VERSION_LESS "3.8")
    message(WARNING "This version of cmake is too old to request C++17 for f5-cord.")
    target_compile_options(f5-cord INTERFACE -std=c++17)
else()
    target_compile_features(f5-cord INTERFACE cxx_std_17)
endif()
install(DIRECTORY include/f5 DESTINATION include)

add_subdirectory(examples)

if(TARGET check)
    set_property(TARGET check PROPERTY EXCLUDE_FROM_ALL TRUE)
    add_subdirectory(test)
endif()
