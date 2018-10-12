//
// Created by zero on 1/17/18.
//

#ifndef ST_CHECKER_ABSYNTAX_VISITOR_H
#define ST_CHECKER_ABSYNTAX_VISITOR_H


#include <string>
#include <iostream>

#include "../libs/matiec/absyntax/visitor.hh"

using std::string;

class AbsyntaxVisitor : public iterator_visitor_c
{
public:
    AbsyntaxVisitor();
    virtual ~AbsyntaxVisitor();

    std::string get_str_statement();
    void init_str_statement();

private:
    static std::string str_statement;

public:

    /***************************/
    /* B 0 - Programming Model */
    /***************************/
    //SYM_LIST(library_c, enumvalue_symtable_t enumvalue_symtable;)


    /*************************/
    /* B.1 - Common elements */
    /*************************/
    /*******************************************/
    /* B 1.1 - Letters, digits and identifiers */
    /*******************************************/
    //SYM_TOKEN(identifier_c)
    void *visit(identifier_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(derived_datatype_identifier_c)
    void *visit(derived_datatype_identifier_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(poutype_identifier_c)
    void *visit(poutype_identifier_c *symbol)
    {
        this->str_statement += (symbol->value);
        return NULL;
    }

    /*********************/
    /* B 1.2 - Constants */
    /*********************/
    /*********************************/
    /* B 1.2.XX - Reference Literals */
    /*********************************/
    //SYM_REF0(ref_value_null_literal_c)
    void *visit(ref_value_null_literal_c *symbol)
    {
        this->str_statement += "NULL";
        return NULL;
    }

    /******************************/
    /* B 1.2.1 - Numeric Literals */
    /******************************/
    //SYM_TOKEN(real_c)
    void *visit(real_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(integer_c)
    void *visit(integer_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(binary_integer_c)
    void *visit(binary_integer_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(octal_integer_c)
    void *visit(octal_integer_c *symbol)
    {
        string value = symbol->value;
        this->str_statement +=value;
        return NULL;
    }

    //SYM_TOKEN(hex_integer_c)
    void *visit(hex_integer_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF1(neg_real_c, exp)
    void *visit(neg_real_c *symbol)
    {
        this->str_statement += "-";
        symbol->exp->accept(*this);
        return NULL;
    }

    //SYM_REF1(neg_integer_c, exp)
    void *visit(neg_integer_c *symbol)
    {
        this->str_statement += "-";
        symbol->exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(integer_literal_c, type, value)
    void *visit(integer_literal_c *symbol)
    {
        symbol->value->accept(*this);
        return NULL;
    }

    //SYM_REF2(real_literal_c, type, value)
    void *visit(real_literal_c *symbol)
    {
        symbol->value->accept(*this);
        return NULL;
    }

    //SYM_REF2(bit_string_literal_c, type, value)
    void *visit(bit_string_literal_c *symbol)
    {
        symbol->value->accept(*this);
        return NULL;
    }

    //SYM_REF2(boolean_literal_c, type, value)
    void *visit(boolean_literal_c *symbol)
    {
        symbol->value->accept(*this);
        return NULL;
    }

    //SYM_REF0(boolean_true_c)
    void *visit(boolean_true_c *symbol)
    {
        this->str_statement += "TRUE";
        return NULL;
    }

    //SYM_REF0(boolean_false_c)
    void *visit(boolean_false_c *symbol)
    {
        this->str_statement += "FALSE";
        return NULL;
    }


    /*******************************/
    /* B.1.2.2   Character Strings */
    /*******************************/
    //SYM_TOKEN(double_byte_character_string_c)
    void *visit(double_byte_character_string_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_TOKEN(single_byte_character_string_c)
    void *visit(single_byte_character_string_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }
    /***************************/
    /* B 1.2.3 - Time Literals */
    /***************************/

    /************************/
    /* B 1.2.3.1 - Duration */
    /************************/
    //SYM_REF0(neg_time_c)
//    void *visit(neg_time_c *symbol)
//    {
//        this->str_statement += "-";
//        return NULL;
//    }

    //SYM_REF3(duration_c, type_name, neg, interval)
    //
    //SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds)
    //SYM_TOKEN(fixed_point_c)

    /************************************/
    /* B 1.2.3.2 - Time of day and Date */
    /************************************/
    //SYM_REF2(time_of_day_c, type_name, daytime)
    //SYM_REF3(daytime_c, day_hour, day_minute, day_second)
    //SYM_REF2(date_c, type_name, date_literal)
    //SYM_REF3(date_literal_c, year, month, day)
    //SYM_REF3(date_and_time_c, type_name, date_literal, daytime)


    /**********************/
    /* B.1.3 - Data types */
    /**********************/
    /***********************************/
    /* B 1.3.1 - Elementary Data Types */
    /***********************************/
    //SYM_REF0(time_type_name_c)
//    void *visit(time_type_name_c *symbol)
//    {
//        string value = symbol->token->value;
//        this->str_statement += value;
//        return NULL;
//    }

    //SYM_REF0(bool_type_name_c)
    void *visit(bool_type_name_c *symbol)
    {
        string value = "BOOL";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(sint_type_name_c)
    void *visit(sint_type_name_c *symbol)
    {
        string value = "SINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(int_type_name_c)
    void *visit(int_type_name_c *symbol)
    {
        string value = "INT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(dint_type_name_c)
    void *visit(dint_type_name_c *symbol)
    {
        string value = "DINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(lint_type_name_c)
    void *visit(lint_type_name_c *symbol)
    {
        string value = "LINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(usint_type_name_c)
    void *visit(usint_type_name_c *symbol)
    {
        string value = "USINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(uint_type_name_c)
    void *visit(uint_type_name_c *symbol)
    {
        string value = "UINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(udint_type_name_c)
    void *visit(udint_type_name_c *symbol)
    {
        string value = "UDINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(ulint_type_name_c)
    void *visit(ulint_type_name_c *symbol)
    {
        string value = "ULINT";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(real_type_name_c)
    void *visit(real_type_name_c *symbol)
    {
        string value = "REAL";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(lreal_type_name_c)
    void *visit(lreal_type_name_c *symbol)
    {
        string value = "LREAL";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(date_type_name_c)
    void *visit(date_type_name_c *symbol)
    {
        string value = symbol->token->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(tod_type_name_c)
    void *visit(tod_type_name_c *symbol)
    {
        string value = symbol->token->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(dt_type_name_c)
    void *visit(dt_type_name_c *symbol)
    {
        string value = symbol->token->value;
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(byte_type_name_c)
    void *visit(byte_type_name_c *symbol)
    {
        string value = "BYTE";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(word_type_name_c)
    void *visit(word_type_name_c *symbol)
    {
        string value = "WORD";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(dword_type_name_c)
    void *visit(dword_type_name_c *symbol)
    {
        string value = "DWORD";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(lword_type_name_c)
    void *visit(lword_type_name_c *symbol)
    {
        string value = "LWORD";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(string_type_name_c)
    void *visit(string_type_name_c *symbol)
    {
        string value = "STRING";
        this->str_statement += value;
        return NULL;
    }

    //SYM_REF0(wstring_type_name_c)
    void *visit(wstring_type_name_c *symbol)
    {
        string value = "WSTRING";
        this->str_statement += value;
        return NULL;
    }


    /*****************************************************************/
    /* Keywords defined in "Safety Software Technical Specification" */
    /*****************************************************************/

    //SYM_REF0(safetime_type_name_c)
    //SYM_REF0(safebool_type_name_c)
    //SYM_REF0(safesint_type_name_c)
    //SYM_REF0(safeint_type_name_c)
    //SYM_REF0(safedint_type_name_c)
    //SYM_REF0(safelint_type_name_c)
    //SYM_REF0(safeusint_type_name_c)
    //SYM_REF0(safeuint_type_name_c)
    //SYM_REF0(safeudint_type_name_c)
    //SYM_REF0(safeulint_type_name_c)
    //SYM_REF0(safereal_type_name_c)
    //SYM_REF0(safelreal_type_name_c)
    //SYM_REF0(safedate_type_name_c)
    //SYM_REF0(safetod_type_name_c)
    //SYM_REF0(safedt_type_name_c)
    //SYM_REF0(safebyte_type_name_c)
    //SYM_REF0(safeword_type_name_c)
    //SYM_REF0(safedword_type_name_c)
    //SYM_REF0(safelword_type_name_c)
    //SYM_REF0(safestring_type_name_c)
    //SYM_REF0(safewstring_type_name_c)


    /********************************/
    /* B.1.3.2 - Generic data types */
    /********************************/

    //SYM_REF0(generic_type_any_c)            // ANY
    void *visit(generic_type_any_c *symbol)
    {
        string value = symbol->token->value;
        this->str_statement += value;
        return NULL;
    }

    /********************************/
    /* B 1.3.3 - Derived data types */
    /********************************/
    //SYM_REF1(data_type_declaration_c, type_declaration_list)
    //
    //SYM_LIST(type_declaration_list_c)
    //
    //SYM_REF2(simple_type_declaration_c, simple_type_name, simple_spec_init)
    //
    //
    //SYM_REF2(simple_spec_init_c, simple_specification, constant)
    //
    //SYM_REF2(subrange_type_declaration_c, subrange_type_name, subrange_spec_init)
    //
    //SYM_REF2(subrange_spec_init_c, subrange_specification, signed_integer)
    //
    //SYM_REF2(subrange_specification_c, integer_type_name, subrange)
    //
    //SYM_REF2(subrange_c, lower_limit, upper_limit, unsigned long long int dimension;)
    //
    //SYM_REF2(enumerated_type_declaration_c, enumerated_type_name, enumerated_spec_init)
    //
    //SYM_REF2(enumerated_spec_init_c, enumerated_specification, enumerated_value)
    //
    //SYM_LIST(enumerated_value_list_c)
    //
    //SYM_REF2(enumerated_value_c, type, value)
    //
    //SYM_REF2(array_type_declaration_c, identifier, array_spec_init)
    //
    //SYM_REF2(array_spec_init_c, array_specification, array_initialization)
    //
    //SYM_REF2(array_specification_c, array_subrange_list, non_generic_type_name)
    //
    //SYM_LIST(array_subrange_list_c)
    //
    //SYM_LIST(array_initial_elements_list_c)
    //
    //SYM_REF2(array_initial_elements_c, integer, array_initial_element)
    //
    //SYM_REF2(structure_type_declaration_c, structure_type_name, structure_specification)
    //
    //SYM_REF2(initialized_structure_c, structure_type_name, structure_initialization)
    //
    //SYM_LIST(structure_element_declaration_list_c)
    //
    //SYM_REF2(structure_element_declaration_c, structure_element_name, spec_init)
    //
    //SYM_LIST(structure_element_initialization_list_c)
    //
    //SYM_REF2(structure_element_initialization_c, structure_element_name, value)
    //
    //SYM_REF4(string_type_declaration_c,	string_type_name,
    //					elementary_string_type_name,
    //					string_type_declaration_size,
    //					string_type_declaration_init) /* may be == NULL! */
    //
    //
    //SYM_REF2(fb_spec_init_c, function_block_type_name, structure_initialization)
    //
    //
    //SYM_REF1(ref_spec_c, type_name)
    //
    //SYM_REF2(ref_spec_init_c, ref_spec, ref_initialization)
    //
    //SYM_REF2(ref_type_decl_c, ref_type_name, ref_spec_init)


    /*********************/
    /* B 1.4 - Variables */
    /*********************/
    //SYM_REF1(symbolic_variable_c, var_name)
    void *visit(symbolic_variable_c *symbol)
    {
        symbol->var_name->accept(*this);
        return NULL;
    }

    //SYM_REF1(symbolic_constant_c, var_name)  // a non-standard extension!!

    /********************************************/
    /* B.1.4.1   Directly Represented Variables */
    /********************************************/
    //SYM_TOKEN(direct_variable_c)
    void *visit(direct_variable_c *symbol)
    {
        string value = symbol->value;
        this->str_statement += value;
        return NULL;
    }

    /*************************************/
    /* B.1.4.2   Multi-element Variables */
    /*************************************/
    //SYM_REF2(array_variable_c, subscripted_variable, subscript_list)
    //
    //SYM_LIST(subscript_list_c)
    //
    //SYM_REF2(structured_variable_c, record_variable, field_selector)

    /******************************************/
    /* B 1.4.3 - Declaration & Initialisation */
    /******************************************/
    //SYM_REF0(constant_option_c)
    //SYM_REF0(retain_option_c)
    //SYM_REF0(non_retain_option_c)
    //
    //SYM_REF3(input_declarations_c, option, input_declaration_list, method)
    //
    //SYM_LIST(input_declaration_list_c)
    //
    //SYM_REF0(implicit_definition_c)
    //SYM_REF0(explicit_definition_c)
    //SYM_REF3(en_param_declaration_c, name, type_decl, method)
    //SYM_REF3(eno_param_declaration_c, name, type, method)
    //
    //SYM_REF2(edge_declaration_c, edge, var1_list)
    //
    //SYM_REF0(raising_edge_option_c)
    //SYM_REF0(falling_edge_option_c)
    //
    //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
    //
    //SYM_LIST(var1_list_c)
    //
    //SYM_REF2(extensible_input_parameter_c, var_name, first_index)
    //
    //SYM_REF2(array_var_init_decl_c, var1_list, array_spec_init)
    //
    //SYM_REF2(structured_var_init_decl_c, var1_list, initialized_structure)
    //
    //SYM_REF2(fb_name_decl_c, fb_name_list, fb_spec_init)
    //
    //SYM_LIST(fb_name_list_c)
    //
    //SYM_REF3(output_declarations_c, option, var_init_decl_list, method)
    //
    //SYM_REF1(input_output_declarations_c, var_declaration_list)
    //
    //SYM_LIST(var_declaration_list_c)
    //
    //SYM_REF2(array_var_declaration_c, var1_list, array_specification)
    //
    //SYM_REF2(structured_var_declaration_c, var1_list, structure_type_name)
    //
    //SYM_REF2(var_declarations_c, option, var_init_decl_list)
    //
    //SYM_REF1(retentive_var_declarations_c, var_init_decl_list)
    //
    //SYM_REF2(located_var_declarations_c, option, located_var_decl_list)
    //
    //SYM_LIST(located_var_decl_list_c)
    //
    //SYM_REF3(located_var_decl_c, variable_name, location, located_var_spec_init)
    //
    //SYM_REF2(external_var_declarations_c, option, external_declaration_list)
    //
    //SYM_LIST(external_declaration_list_c)
    //
    //SYM_REF2(external_declaration_c, global_var_name, specification)
    //
    //SYM_REF2(global_var_declarations_c, option, global_var_decl_list)
    //
    //SYM_LIST(global_var_decl_list_c)
    //
    //SYM_REF2(global_var_decl_c, global_var_spec, type_specification)
    //
    //SYM_REF2(global_var_spec_c, global_var_name, location)
    //
    //SYM_REF1(location_c, direct_variable)
    //
    //SYM_LIST(global_var_list_c)
    //
    //SYM_REF2(single_byte_string_var_declaration_c, var1_list, single_byte_string_spec)
    //
    //SYM_REF2(single_byte_string_spec_c, string_spec, single_byte_character_string)
    //
    //SYM_REF2(single_byte_limited_len_string_spec_c, string_type_name, character_string_len)
    //
    //SYM_REF2(double_byte_limited_len_string_spec_c, string_type_name, character_string_len)
    //
    //SYM_REF2(double_byte_string_var_declaration_c, var1_list, double_byte_string_spec)
    //
    //SYM_REF2(double_byte_string_spec_c, string_spec, double_byte_character_string)
    //
    //SYM_REF2(incompl_located_var_declarations_c, option, incompl_located_var_decl_list)
    //
    //SYM_LIST(incompl_located_var_decl_list_c)
    //
    //SYM_REF3(incompl_located_var_decl_c, variable_name, incompl_location, var_spec)
    //
    //SYM_TOKEN(incompl_location_c)
    //
    //SYM_LIST(var_init_decl_list_c)




    /**************************************/
    /* B.1.5 - Program organization units */
    /**************************************/
    /***********************/
    /* B 1.5.1 - Functions */
    /***********************/
    //SYM_REF4(function_declaration_c, derived_function_name, type_name, var_declarations_list, function_body, enumvalue_symtable_t enumvalue_symtable;)
    //
    //SYM_LIST(var_declarations_list_c)
    //
    //SYM_REF2(function_var_decls_c, option, decl_list)
    //
    //SYM_LIST(var2_init_decl_list_c)


    /*****************************/
    /* B 1.5.2 - Function Blocks */
    /*****************************/
    //SYM_REF3(function_block_declaration_c, fblock_name, var_declarations, fblock_body, enumvalue_symtable_t enumvalue_symtable;)
    //
    //SYM_REF1(temp_var_decls_c, var_decl_list)
    //
    //SYM_LIST(temp_var_decls_list_c)
    //
    //SYM_REF1(non_retentive_var_decls_c, var_decl_list)


    /**********************/
    /* B 1.5.3 - Programs */
    /**********************/
    //SYM_REF3(program_declaration_c, program_type_name, var_declarations, function_block_body, enumvalue_symtable_t enumvalue_symtable;)


    /*********************************************/
    /* B.1.6  Sequential function chart elements */
    /*********************************************/

    //SYM_LIST(sequential_function_chart_c)
    //
    //SYM_LIST(sfc_network_c)
    //
    //SYM_REF2(initial_step_c, step_name, action_association_list)
    //
    //SYM_LIST(action_association_list_c)
    //
    //SYM_REF2(step_c, step_name, action_association_list)
    //
    //SYM_REF3(action_association_c, action_name, action_qualifier, indicator_name_list)
    //
    //SYM_TOKEN(qualifier_c)
    //
    //SYM_TOKEN(timed_qualifier_c)
    //
    //SYM_LIST(indicator_name_list_c)
    //
    //SYM_REF2(action_qualifier_c, action_qualifier, action_time)
    //
    //SYM_REF5(transition_c, transition_name, integer, from_steps, to_steps, transition_condition)
    //
    //SYM_REF2(transition_condition_c, transition_condition_il, transition_condition_st)
    //
    //SYM_REF2(steps_c, step_name, step_name_list)
    //
    //SYM_LIST(step_name_list_c)
    //
    //SYM_REF2(action_c, action_name, function_block_body)

    /********************************/
    /* B 1.7 Configuration elements */
    /********************************/

    /*
    CONFIGURATION configuration_name
       optional_global_var_declarations
       (resource_declaration_list | single_resource_declaration)
       optional_access_declarations
       optional_instance_specific_initializations
    END_CONFIGURATION
    */
    /* enumvalue_symtable is filled in by enum_declaration_check_c, during stage3 semantic verification, with a list of all enumerated constants declared inside this POU */
    //SYM_REF5(configuration_declaration_c, configuration_name, global_var_declarations, resource_declarations, access_declarations, instance_specific_initializations, enumvalue_symtable_t enumvalue_symtable;)

    /* intermediate helper symbol for configuration_declaration  */
    /*  { global_var_declarations_list }   */
    //SYM_LIST(global_var_declarations_list_c)

    /* helper symbol for configuration_declaration */
    //SYM_LIST(resource_declaration_list_c)

    /*
    RESOURCE resource_name ON resource_type_name
       optional_global_var_declarations
       single_resource_declaration
    END_RESOURCE
    */
    /* enumvalue_symtable is filled in by enum_declaration_check_c, during stage3 semantic verification, with a list of all enumerated constants declared inside this POU */
    //SYM_REF4(resource_declaration_c, resource_name, resource_type_name, global_var_declarations, resource_declaration, enumvalue_symtable_t enumvalue_symtable;)

    /* task_configuration_list program_configuration_list */
    //SYM_REF2(single_resource_declaration_c, task_configuration_list, program_configuration_list)

    /* helper symbol for single_resource_declaration */
    //SYM_LIST(task_configuration_list_c)

    /* helper symbol for single_resource_declaration */
    //SYM_LIST(program_configuration_list_c)

    /* helper symbol for
     *  - access_path
     *  - instance_specific_init
     */
    //SYM_LIST(any_fb_name_list_c)

    /*  [resource_name '.'] global_var_name ['.' structure_element_name] */
    //SYM_REF3(global_var_reference_c, resource_name, global_var_name, structure_element_name)

    /*  prev_declared_program_name '.' symbolic_variable */
    //SYM_REF2(program_output_reference_c, program_name, symbolic_variable)

    /*  TASK task_name task_initialization */
    //SYM_REF2(task_configuration_c, task_name, task_initialization)

    /*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
    //SYM_REF3(task_initialization_c, single_data_source, interval_data_source, priority_data_source)

    /*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
    //SYM_REF5(program_configuration_c, retain_option, program_name, task_name, program_type_name, prog_conf_elements)

    /* prog_conf_elements ',' prog_conf_element */
    //SYM_LIST(prog_conf_elements_c)

    /*  fb_name WITH task_name */
    //SYM_REF2(fb_task_c, fb_name, task_name)

    /*  any_symbolic_variable ASSIGN prog_data_source */
    //SYM_REF2(prog_cnxn_assign_c, symbolic_variable, prog_data_source)

    /* any_symbolic_variable SENDTO data_sink */
    //SYM_REF2(prog_cnxn_sendto_c, symbolic_variable, data_sink)

    /* VAR_CONFIG instance_specific_init_list END_VAR */
    //SYM_REF1(instance_specific_initializations_c, instance_specific_init_list)

    /* helper symbol for instance_specific_initializations */
    //SYM_LIST(instance_specific_init_list_c)

    /* resource_name '.' program_name '.' {fb_name '.'}
        ((variable_name [location] ':' located_var_spec_init) | (fb_name ':' fb_initialization))
    */
    //SYM_REF6(instance_specific_init_c, resource_name, program_name, any_fb_name_list, variable_name, location, initialization)

    /* helper symbol for instance_specific_init */
    /* function_block_type_name ':=' structure_initialization */
    //SYM_REF2(fb_initialization_c, function_block_type_name, structure_initialization)



    /****************************************/
    /* B.2 - Language IL (Instruction List) */
    /****************************************/
    /***********************************/
    /* B 2.1 Instructions and Operands */
    /***********************************/
    /*| instruction_list il_instruction */
    //SYM_LIST(instruction_list_c)

    /* | label ':' [il_incomplete_instruction] eol_list */
    /* NOTE: The parameters 'prev_il_instruction'/'next_il_instruction' are used to point to all previous/next il instructions that may be executed imedaitely before/after this instruction.
     *       In case of an il instruction preceded by a label, the previous_il_instruction will include all IL instructions that jump to this label!
     *       It is filled in by the flow_control_analysis_c during stage 3.
     *       This will essentially be a doubly linked list of il_instruction_c and il_simple_instruction_c objects!!
     */
    //SYM_REF2(il_instruction_c, label, il_instruction, std::vector <symbol_c *> prev_il_instruction, next_il_instruction;)


    /* | il_simple_operator [il_operand] */
    //SYM_REF2(il_simple_operation_c, il_simple_operator, il_operand)

    /* | function_name [il_operand_list] */
    /* NOTE: The parameter 'called_function_declaration', 'extensible_param_count' and 'candidate_functions' are used to pass data between the stage 3 and stage 4.
     *       data between the stage 3 and stage 4.
     *       See the comment above function_invocation_c for more details
     */
    //SYM_REF2(il_function_call_c, function_name, il_operand_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)


    /* | il_expr_operator '(' [il_operand] eol_list [simple_instr_list] ')' */
    /* WARNING
     *   The semantics of the il_expression_c.il_operand member is NOT what you may expect!
     *   In order to simplify processing of the IL code, stage2 will prepend an artifical (and equivalent) 'LD <il_operand>' IL instruction into the simple_instr_list
     *   The il_expression_c.il_operand is maintained, in case we really need to handle it as a special case!
     *   See the comments in iec_bison.yy for details and an example.
     */
    //SYM_REF3(il_expression_c, il_expr_operator, il_operand, simple_instr_list)

    /*  il_jump_operator label */
    //SYM_REF2(il_jump_operation_c, il_jump_operator, label)

    /*   il_call_operator prev_declared_fb_name
     * | il_call_operator prev_declared_fb_name '(' ')'
     * | il_call_operator prev_declared_fb_name '(' eol_list ')'
     * | il_call_operator prev_declared_fb_name '(' il_operand_list ')'
     * | il_call_operator prev_declared_fb_name '(' eol_list il_param_list ')'
     */
    /* NOTE: The parameter 'called_fb_declaration'is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
    //SYM_REF4(il_fb_call_c, il_call_operator, fb_name, il_operand_list, il_param_list, symbol_c *called_fb_declaration;)


    /* | function_name '(' eol_list [il_param_list] ')' */
    /* NOTE: The parameter 'called_function_declaration', 'extensible_param_count' and 'candidate_functions' are used to pass data between the stage 3 and stage 4.
     *       See the comment above function_invocation_c for more details.
     */
    //SYM_REF2(il_formal_funct_call_c, function_name, il_param_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)

    /* | il_operand_list ',' il_operand */
    //SYM_LIST(il_operand_list_c)

    /* | simple_instr_list il_simple_instruction */
    //SYM_LIST(simple_instr_list_c)


    /* il_simple_instruction:
     *   il_simple_operation eol_list
     * | il_expression eol_list
     * | il_formal_funct_call eol_list
     */
    /* NOTE: The parameters 'prev_il_instruction'/'next_il_instruction' are used to point to all previous/next il instructions that may be executed imedaitely before/after this instruction.
     *       In case of an il instruction preceded by a label, the previous_il_instruction will include all IL instructions that jump to this label!
     *       It is filled in by the flow_control_analysis_c during stage 3.
     *       This will essentially be a doubly linked list of il_instruction_c and il_simple_instruction_c objects!!
     */
    //SYM_REF1(il_simple_instruction_c, il_simple_instruction, std::vector <symbol_c *> prev_il_instruction, next_il_instruction;)

    /* | il_initial_param_list il_param_instruction */
    //SYM_LIST(il_param_list_c)

    /*  il_assign_operator il_operand
     * | il_assign_operator '(' eol_list simple_instr_list ')'
     */
    //SYM_REF3(il_param_assignment_c, il_assign_operator, il_operand, simple_instr_list)

    /*  il_assign_out_operator variable */
    //SYM_REF2(il_param_out_assignment_c, il_assign_out_operator, variable)



    /*******************/
    /* B 2.2 Operators */
    /*******************/
    /* NOTE: The parameter 'called_fb_declaration' is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
    /* NOTE: The parameter 'deprecated_operation' indicates that the operation, with the specific data types being used, is currently defined
     *       in the standard as being deprecated. This variable is filled in with the correct value in stage 3 (narrow_candidate_datatypes_c)
     *       and currently only used in stage 3 (print_datatypes_error_c).
     */
    //SYM_REF0(LD_operator_c)
    //SYM_REF0(LDN_operator_c)
    //SYM_REF0(ST_operator_c)
    //SYM_REF0(STN_operator_c)
    //SYM_REF0(NOT_operator_c)
    //SYM_REF0(S_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(R_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(S1_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(R1_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(CLK_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(CU_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(CD_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(PV_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(IN_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(PT_operator_c, symbol_c *called_fb_declaration;)
    //SYM_REF0(AND_operator_c)
    //SYM_REF0(OR_operator_c)
    //SYM_REF0(XOR_operator_c)
    //SYM_REF0(ANDN_operator_c)
    //SYM_REF0(ORN_operator_c)
    //SYM_REF0(XORN_operator_c)
    //SYM_REF0(ADD_operator_c, bool deprecated_operation;)
    //SYM_REF0(SUB_operator_c, bool deprecated_operation;)
    //SYM_REF0(MUL_operator_c, bool deprecated_operation;)
    //SYM_REF0(DIV_operator_c, bool deprecated_operation;)
    //SYM_REF0(MOD_operator_c)
    //SYM_REF0(GT_operator_c)
    //SYM_REF0(GE_operator_c)
    //SYM_REF0(EQ_operator_c)
    //SYM_REF0(LT_operator_c)
    //SYM_REF0(LE_operator_c)
    //SYM_REF0(NE_operator_c)
    //SYM_REF0(CAL_operator_c)
    //SYM_REF0(CALC_operator_c)
    //SYM_REF0(CALCN_operator_c)
    //SYM_REF0(RET_operator_c)
    //SYM_REF0(RETC_operator_c)
    //SYM_REF0(RETCN_operator_c)
    //SYM_REF0(JMP_operator_c)
    //SYM_REF0(JMPC_operator_c)
    //SYM_REF0(JMPCN_operator_c)

    /*  any_identifier ASSIGN */
    //SYM_REF1(il_assign_operator_c, variable_name)

    /*| [NOT] any_identifier SENDTO */
    //SYM_REF2(il_assign_out_operator_c, option, variable_name)



    /***************************************/
    /* B.3 - Language ST (Structured Text) */
    /***************************************/
    /***********************/
    /* B 3.1 - Expressions */
    /***********************/
    //SYM_REF1(  ref_expression_c, exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard.  REF() -> returns address of the varible! */
    //SYM_REF1(deref_expression_c, exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard. DREF() -> dereferences an address!        */
    //SYM_REF1(deref_operator_c,   exp)  /* an extension to the IEC 61131-3 standard - based on the IEC 61131-3 v3 standard.    ^   -> dereferences an address!        */
    //SYM_REF2( or_expression_c, l_exp, r_exp)
    void *visit(or_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " OR ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(xor_expression_c, l_exp, r_exp)
    void *visit(xor_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " XOR ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(and_expression_c, l_exp, r_exp)
    void *visit(and_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " AND ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(equ_expression_c, l_exp, r_exp)
    void *visit(equ_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " = ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(notequ_expression_c, l_exp, r_exp)
    void *visit(notequ_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " <> ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2( lt_expression_c, l_exp, r_exp)
    void *visit(lt_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " < ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2( gt_expression_c, l_exp, r_exp)
    void *visit(gt_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " > ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2( le_expression_c, l_exp, r_exp)
    void *visit(le_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " <= ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2( ge_expression_c, l_exp, r_exp)
    void *visit(ge_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " >= ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(add_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(add_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " + ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(sub_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(sub_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " - ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(mul_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(mul_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " * ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(div_expression_c, l_exp, r_exp, bool deprecated_operation;)
    void *visit(div_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " / ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(mod_expression_c, l_exp, r_exp)
    void *visit(mod_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " MOD ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF2(power_expression_c, l_exp, r_exp)
    void *visit(power_expression_c *symbol)
    {
        symbol->l_exp->accept(*this);
        this->str_statement += " POW ";
        symbol->r_exp->accept(*this);
        return NULL;
    }

    //SYM_REF1(neg_expression_c, exp)
    void *visit(neg_expression_c *symbol)
    {
        this->str_statement += "-";
        symbol->exp->accept(*this);
        return NULL;
    }

    //SYM_REF1(not_expression_c, exp)
    void *visit(not_expression_c *symbol)
    {
        this->str_statement += "NOT ";
        symbol->exp->accept(*this);
        return NULL;
    }

    //SYM_REF3(function_invocation_c, function_name, formal_param_list, nonformal_param_list, symbol_c *called_function_declaration; int extensible_param_count; std::vector <symbol_c *> candidate_functions;)
    void *visit(function_invocation_c *symbol)
    {
        symbol->function_name->accept(*this);
        this->str_statement += ("(");
        this->str_statement
                += ")";
        return NULL;
    }


    /********************/
    /* B 3.2 Statements */
    /********************/
    //SYM_LIST(statement_list_c)


    /*********************************/
    /* B 3.2.1 Assignment Statements */
    /*********************************/
    //SYM_REF2(assignment_statement_c, l_exp, r_exp)
    void *visit(assignment_statement_c *symbol);

    /*****************************************/
    /* B 3.2.2 Subprogram Control Statements */
    /*****************************************/

    /*  RETURN */
    //SYM_REF0(return_statement_c)
    void *visit(return_statement_c *symbol);

    /* fb_name '(' [param_assignment_list] ')' */
    /*    formal_param_list -> may be NULL ! */
    /* nonformal_param_list -> may be NULL ! */
    /* NOTE: The parameter 'called_fb_declaration'is used to pass data between stage 3 and stage4 (although currently it is not used in stage 4 */
    //SYM_REF3(fb_invocation_c, fb_name, formal_param_list, nonformal_param_list, symbol_c *called_fb_declaration;)
    void *visit(fb_invocation_c *symbol);

    /* helper symbol for fb_invocation */
    /* param_assignment_list ',' param_assignment */
    //SYM_LIST(param_assignment_list_c)
    void *visit(param_assignment_list_c *symbol);

    /*  variable_name ASSIGN expression */
    //SYM_REF2(input_variable_param_assignment_c, variable_name, expression)
    void *visit(input_variable_param_assignment_c *symbol);

    /* [NOT] variable_name '=>' variable */
    //SYM_REF3(output_variable_param_assignment_c, not_param, variable_name, variable)
    void *visit(output_variable_param_assignment_c *symbol);

    /* helper CLASS for output_variable_param_assignment */
    //SYM_REF0(not_paramassign_c)
    void *visit(not_paramassign_c *symbol);


    /********************************/
    /* B 3.2.3 Selection Statements */
    /********************************/
    /* IF expression THEN statement_list elseif_statement_list ELSE statement_list END_IF */
    //SYM_REF4(if_statement_c, expression, statement_list, elseif_statement_list, else_statement_list)
    void *visit(if_statement_c *symbol);

    /* helper symbol for if_statement */
    //SYM_LIST(elseif_statement_list_c)
    void *visit(elseif_statement_list_c *symbol);

    /* helper symbol for elseif_statement_list */
    /* ELSIF expression THEN statement_list    */
    //SYM_REF2(elseif_statement_c, expression, statement_list)
    void *visit(elseif_statement_c *symbol);

    /* CASE expression OF case_element_list ELSE statement_list END_CASE */
    //SYM_REF3(case_statement_c, expression, case_element_list, statement_list)
    void *visit(case_statement_c *symbol);

    /* helper symbol for case_statement */
    //SYM_LIST(case_element_list_c)
    void *visit(case_element_list_c *symbol);

    /*  case_list ':' statement_list */
    //SYM_REF2(case_element_c, case_list, statement_list)
    void *visit(case_element_c *symbol);

    //SYM_LIST(case_list_c)
    void *visit(case_list_c *symbol);


    /********************************/
    /* B 3.2.4 Iteration Statements */
    /********************************/
    /*  FOR control_variable ASSIGN expression TO expression [BY expression] DO statement_list END_FOR */
    //SYM_REF5(for_statement_c, control_variable, beg_expression, end_expression, by_expression, statement_list)
    void *visit(for_statement_c *symbol);

    /*  WHILE expression DO statement_list END_WHILE */
    //SYM_REF2(while_statement_c, expression, statement_list)
    void *visit(while_statement_c *symbol);

    /*  REPEAT statement_list UNTIL expression END_REPEAT */
    //SYM_REF2(repeat_statement_c, statement_list, expression)
    void *visit(repeat_statement_c *symbol);

    /*  EXIT */
    //SYM_REF0(exit_statement_c)
    void *visit(exit_statement_c *symbol);
};


#endif //ST_CHECKER_ABSYNTAX_VISITOR_H
