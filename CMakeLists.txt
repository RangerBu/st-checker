cmake_minimum_required(VERSION 3.9)
project(st_checker)

add_definitions("-D_GLIBCXX_USE_CXX11_ABI=0")
add_definitions("-Woverflow")

set(CMAKE_CXX_STANDARD 11)

link_directories(libs/wali/ libs/matiec/stage1_2/ libs/matiec/absyntax/ libs/matiec/absyntax_utils/)
include_directories(libs/wali/ )

add_executable(st_checker main.cpp
        analyzer/domain/value_set.cpp
        analyzer/domain/var.cpp
        analyzer/structures/abstract_data.cpp
        analyzer/structures/bits_vector.cpp
        analyzer/structures/bits_vector_1.hpp
        analyzer/structures/bits_vector_8.hpp
        analyzer/structures/boolean4.cpp
        analyzer/structures/strided_interval.cpp
        analyzer/transformer/assign_stmt_transfer.cpp
        analyzer/transformer/elif_stmt_transfer.cpp
        analyzer/transformer/if_stmt_transfer.cpp
        analyzer/transformer/value_set_transfer.cpp
        builder/flow-graph-builder/node.cpp
        builder/flow-graph-builder/edge.cpp
        builder/flow-graph-builder/cfg.cpp
        builder/flow-graph-builder/cfg_builder.cpp
        builder/model-builder/structures/cts.cpp
        builder/model-builder/structures/program_state.cpp
        builder/model-builder/structures/transition_rule.cpp
        builder/model-builder/structures/value_set_semiring.cpp
        builder/model-builder/cts_builder.cpp
        builder/model-builder/wpds_builder.cpp
        parser/absyntax_visitor.cpp
        parser/absyntax_visitor.h
        parser/st_parser.cpp
        test/model-builder/transfer_semiring_test.cpp
        test/model-builder/value_set_semiring_test.cpp
        test/model-builder/wpds_builder_test.cpp
        test/builder_test.cpp
        test/domain_test.cpp
        test/flow_graph_builder_test.cpp
        test/structures_test.cpp
        test/transfer_test.cpp
        )

target_link_libraries(st_checker wali stage1_2 absyntax absyntax_utils)

add_subdirectory(libs/matiec)
add_subdirectory(libs/wali)