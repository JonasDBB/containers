cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g3 -fsanitize=address")
set(CMAKE_LINKER_FLAGS)

add_executable(tests testmain.cpp ft_vector.hpp RandomAccessIterator.hpp type_traits.hpp)
set_target_properties(tests PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 98)
#target_include_directories(tests ${dirname})