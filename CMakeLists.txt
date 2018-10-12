cmake_minimum_required(VERSION 3.6)
project(verify_st_programs)

set(CMAKE_CXX_STANDARD 11)

include_directories(parser/matiec/)
include_directories(simulator/)

set(STRUCTURES_SRC
        parser/structures/program.cpp
        parser/structures/program.h
        parser/structures/pou.cpp
        parser/structures/pou.h
        parser/structures/function.cpp
        parser/structures/function.h
        parser/structures/function_block.cpp
        parser/structures/function_block.h
        parser/structures/vertex.cpp
        parser/structures/vertex.h
        parser/structures/edge.cpp
        parser/structures/edge.h
        parser/structures/cfg.cpp
        parser/structures/cfg.h
        parser/structures/variable.cpp
        parser/structures/variable.h
        parser/structures/abstract_value.cpp
        parser/structures/abstract_value.h
        parser/structures/extended_boolean.cpp
        parser/structures/extended_boolean.h
        parser/structures/interval.cpp
        parser/structures/interval.h
        simulator/structures/semiring.cpp
        simulator/structures/semiring.h simulator/structures/configuration.cpp simulator/structures/configuration.h simulator/structures/stack_symbol.cpp simulator/structures/stack_symbol.h simulator/structures/value_assignment.cpp simulator/structures/value_assignment.h)

add_library(structures ${STRUCTURES_SRC})

add_executable(checker main.cpp
        parser/parser.cpp
        parser/parser.h
        debug_helper.cpp
        debug_helper.h
        parser/utils.cpp
        parser/utils.h
        parser/visitors/symbol_to_string_visitor.cpp
        parser/visitors/symbol_to_string_visitor.h
        simulator/abstract_simulator.cpp
        simulator/abstract_simulator.h
        )

target_link_libraries(checker matiec structures wali)

add_subdirectory(parser/matiec/)
add_subdirectory(simulator/wali)
