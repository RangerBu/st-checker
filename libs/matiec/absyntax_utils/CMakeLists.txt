cmake_minimum_required(VERSION 3.9)
project(st_checker)

add_library(absyntax_utils
        absyntax_utils.cc
        add_en_eno_param_decl.cc
        array_dimension_iterator.cc
        case_element_iterator.cc
        debug_ast.cc
        decompose_var_instance_name.cc
        function_call_iterator.cc
        function_call_param_iterator.cc
        function_param_iterator.cc
        get_datatype_info.cc
        get_sizeof_datatype.cc
        get_var_name.cc
        search_base_type.cc
        search_fb_instance_decl.cc
        search_fb_typedecl.cc
        search_il_label.cc
        search_var_instance_decl.cc
        search_varfb_instance_type.cc
        spec_init_separator.cc
        type_initial_value.cc)
