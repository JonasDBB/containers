cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_LINKER_FLAGS)

add_library(ft_containers ft_vector.hpp)
set_target_properties(ft_containers PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 98)

add_executable(tests testmain.cpp )