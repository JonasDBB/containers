cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)
SET(DEBUGFLAGS "-fsanitize=address -D ASAN")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -g3 ${DEBUGFLAGS}")
set(CMAKE_LINKER_FLAGS)

add_executable( tests
                srcs/testmain.cpp

                srcs/containers/ft_vector.hpp
                srcs/containers/ft_stack.hpp
                srcs/containers/ft_queue.hpp
#                srcs/containers/ft_list.hpp
				srcs/containers/ft_map.hpp

                srcs/iterators/RandomAccessIterator.hpp
                srcs/iterators/ReverseIterator.hpp
                srcs/iterators/BidirectionalIterator.hpp
				srcs/iterators/NodeIterator.hpp

                srcs/utils/type_traits.hpp
                srcs/utils/Utils.hpp
        		srcs/utils/ANode.hpp
#        		srcs/utils/ListNode.hpp
				srcs/utils/ft_pair.hpp
				srcs/utils/MapNode.hpp
				)

add_executable( catch
                catch2tests/main.cpp
                catch2tests/catch.cpp
                catch2tests/catch.hpp

                catch2tests/vector_tests.cpp
                catch2tests/stack_tests.cpp
                catch2tests/queue_tests.cpp
				catch2tests/list_tests.cpp
#				catch2tests/map_tests.cpp
				)

add_executable(	trees
				srcs/treetest.cpp
				srcs/containers/ft_map.hpp
				srcs/iterators/BidirectionalIterator.hpp
				srcs/iterators/NodeIterator.hpp
				srcs/utils/type_traits.hpp
				srcs/utils/Utils.hpp
				srcs/utils/ANode.hpp
				srcs/utils/ft_pair.hpp
				srcs/utils/MapNode.hpp
				)

set_target_properties(tests PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 98)
set_target_properties(trees PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 98)
set_source_files_properties(catch2tests/catch.cpp catch2tests/catch.hpp PROPERTIES COMPILE_FLAGS "-std=c++14")