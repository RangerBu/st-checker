find_package(FLEX)
find_package(BISON)


bison_target(Parser ${CMAKE_CURRENT_SOURCE_DIR}/stage1_2/iec_bison.yy ${CMAKE_CURRENT_BINARY_DIR}/iec_bison.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/iec_bison.hh)
flex_target(Scanner ${CMAKE_CURRENT_SOURCE_DIR}/stage1_2/iec_flex.ll  ${CMAKE_CURRENT_BINARY_DIR}/iec_flex.cpp)

add_flex_bison_dependency(Scanner Parser)

include_directories(absyntax absyntax_utils stage1_2 util ${CMAKE_CURRENT_BINARY_DIR})

set(MATIEC_SRC
        absyntax/absyntax.def absyntax/absyntax.cc absyntax/visitor.cc
        absyntax_utils/absyntax_utils.cc
        absyntax_utils/add_en_eno_param_decl.cc
        absyntax_utils/array_dimension_iterator.cc
        absyntax_utils/case_element_iterator.cc
        absyntax_utils/debug_ast.cc
        absyntax_utils/decompose_var_instance_name.cc
        absyntax_utils/function_call_iterator.cc
        absyntax_utils/function_call_param_iterator.cc
        absyntax_utils/function_param_iterator.cc
        absyntax_utils/get_datatype_info.cc
        absyntax_utils/get_sizeof_datatype.cc
        absyntax_utils/get_var_name.cc
        absyntax_utils/search_base_type.cc
        absyntax_utils/search_fb_instance_decl.cc
        absyntax_utils/search_fb_typedecl.cc
        absyntax_utils/search_il_label.cc
        absyntax_utils/search_var_instance_decl.cc
        absyntax_utils/search_varfb_instance_type.cc
        absyntax_utils/spec_init_separator.cc
        absyntax_utils/type_initial_value.cc
        stage1_2/stage1_2.cc
        stage1_2/create_enumtype_conversion_functions.cc
        stage1_2/iec_flex.ll
        stage1_2/iec_bison.yy
        ${FLEX_Scanner_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
        )

add_library(matiec ${MATIEC_SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})