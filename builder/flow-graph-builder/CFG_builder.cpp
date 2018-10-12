//
// Created by zero on 1/18/18.
//

#include "cfg_builder.h"

/**
* static methods
*/
CFG_builder *CFG_builder::get_instance()
{
    if (builder == 0)
    {
        builder = new CFG_builder();
    }
    return builder;
}


/**
* public methods
*/
CFG_builder::~CFG_builder()
{
}


/**
* external
*/
CFG *CFG_builder::create_CFG(ST_parser *_parser)
{
    CFG *ret = new CFG(_parser->get_stmts_list());

    std::vector<Var *> var_list;
    var_declarations_list_c *var_decls = _parser->get_vars();

    int len = var_decls->n;
    for (int i=0; i<len; i++)
    {
        symbol_c *elem = var_decls->get_element(i);
        std::string cname = elem->absyntax_cname();

        //SYM_REF3(input_declarations_c, option, input_declaration_list, method)
        if (cname.compare("input_declarations_c") == 0)
        {
            input_declarations_c *input_declarations = (input_declarations_c *) elem;
            //SYM_LIST(var_init_decl_list_c)
            input_declaration_list_c *input_declaration_list = (input_declaration_list_c *)input_declarations->input_declaration_list;
            int nn = input_declaration_list->n;
            for (int j = 0; j < nn; j++)
            {
                //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)input_declaration_list-> get_element(j);
                //SYM_LIST(var1_list_c)
                var1_list_c *var1_list = (var1_list_c *)var1_init_decl->var1_list;
                //SYM_REF2(simple_spec_init_c, simple_specification, constant)
                simple_spec_init_c *spec_init = (simple_spec_init_c *)var1_init_decl->spec_init;

                /* str_type */
                std::string simple_specification = ST_parser::parse(spec_init->simple_specification);

                /* str_constant*/
                std::string constant = "";
                if (spec_init->constant != 0)
                {
                    constant = ST_parser::parse(spec_init->constant);
                }

                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    /* str_name */
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    Var *new_var = new Var(name, simple_specification, Var::SEMANTICS_INPUT);
                    new_var->set_str_constant(constant);

                    var_list.push_back(new_var);
                }
            }
        }
            //SYM_REF3(output_declarations_c, option, var_init_decl_list, method)
        else if (cname.compare("output_declarations_c") == 0)
        {
            output_declarations_c *output_declarations = (output_declarations_c *)elem;

            //SYM_LIST(var_init_decl_list_c)
            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *)output_declarations->var_init_decl_list;
            int nn = var_init_decl_list->n;
            for (int j = 0; j < nn; j++)
            {
                //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list-> get_element(j);
                //SYM_LIST(var1_list_c)
                var1_list_c *var1_list = (var1_list_c *)var1_init_decl->var1_list;
                //SYM_REF2(simple_spec_init_c, simple_specification, constant)
                simple_spec_init_c *spec_init = (simple_spec_init_c *)var1_init_decl->spec_init;

                /* str_type */
                std::string simple_specification = ST_parser::parse(spec_init->simple_specification);

                /* str_constant */
                std::string constant = "";
                if (spec_init->constant != 0)
                {
                    constant = ST_parser::parse(spec_init->constant);
                }

                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    /* str_name */
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    Var *new_var = new Var(name, simple_specification, Var::SEMANTICS_OUTPUT);
                    new_var->set_str_constant(constant);

                    var_list.push_back(new_var);
                }
            }
        }
            //SYM_REF1(input_output_declarations_c, var_declaration_list)
        else if (cname.compare("input_output_declarations_c") == 0)
        {

        }
            //SYM_REF2(var_declarations_c, option, var_init_decl_list)
        else if (cname.compare("var_declarations_c") == 0)
        {
            var_declarations_c *var_decl_list = (var_declarations_c *)elem;
            //SYM_LIST(var_init_decl_list_c)
            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *)var_decl_list->var_init_decl_list;
            int nn = var_init_decl_list->n;
            for (int j = 0; j < nn; j++)
            {
                //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list-> get_element(j);
                //SYM_LIST(var1_list_c)
                var1_list_c *var1_list = (var1_list_c *)var1_init_decl->var1_list;
                //SYM_REF2(simple_spec_init_c, simple_specification, constant)
                simple_spec_init_c *spec_init = (simple_spec_init_c *)var1_init_decl->spec_init;

                std::string simple_specification = ST_parser::parse(spec_init->simple_specification);

                std::string constant = "";
                if(spec_init->constant != 0)
                {
                    constant = ST_parser::parse(spec_init->constant);
                }

                /*
                 * add the support for binary/octal/hex integer
                 */
                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    Var *new_var = new Var(name, simple_specification, Var::SEMANTICS_VAR);
                    new_var->set_str_constant(constant);

                    var_list.push_back(new_var);
                }
            }
        }
            //SYM_REF1(retentive_var_declarations_c, var_init_decl_list)
        else if (cname.compare("retentive_var_declarations_c") == 0)
        {
//            retentive_var_declarations_c *var_decl_list = (retentive_var_declarations_c *)elem;
//            //SYM_LIST(var_init_decl_list_c)
//            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *)var_decl_list->var_init_decl_list;
//            int nn = var_init_decl_list->n;
//
//            for (int j = 0; j < nn; j++)
//            {
//                //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
//                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list->get_element(j);
//                //SYM_LIST(var1_list_c)
//                var1_list_c *var1_list = (var1_list_c *)var1_init_decl->var1_list;
//                //SYM_REF2(simple_spec_init_c, simple_specification, constant)
//                simple_spec_init_c *spec_init = (simple_spec_init_c *)var1_init_decl->spec_init;
//
//                std::string simple_specification = ST_parser::parse(spec_init->simple_specification);
//
//                /*
//                 * parse the initial value of the variable
//                 */
//                std::string constant = "";
//                if(spec_init->constant != 0)
//                {
//                    constant = ST_parser::parse(spec_init->constant);
//                }
//
//                int nnn = var1_list->n;
//                for (int k = 0; k < nnn; k++)
//                {
//                    std::string name = ST_parser::parse(var1_list->get_element(k));
//
//                    Var *new_var = new Var(name, simple_specification, Var::SEMANTICS_RETENTIVE);
//                    new_var->set_str_constant(constant);
//
//                    var_list.push_back(new_var);
//                }
//            }
        }
            //SYM_REF2(located_var_declarations_c, option, located_var_decl_list)
        else if (cname.compare("located_var_declarations_c") == 0)
        {

//            located_var_declarations_c *located_var_declarations = (located_var_declarations_c *)elem;
//            if (located_var_declarations->option != 0)
//            {
//                //SYM_LIST(located_var_decl_list_c)
//                located_var_decl_list_c *located_var_decl_list = (located_var_decl_list_c *)located_var_declarations->located_var_decl_list;
//
//                int nn = located_var_decl_list->n;
//                for (int j = 0; j < nn; j++)
//                {
//                    //SYM_REF3(located_var_decl_c, variable_name, location, located_var_spec_init)
//                    located_var_decl_c *located_var_decl = (located_var_decl_c *) located_var_decl_list->get_element(j);
//
//                    //SYM_TOKEN(identifier_c)
//                    std::string variable_name = ((identifier_c *)located_var_decl->variable_name)->value;
//
//                    //SYM_REF1(location_c, direct_variable)
//                    std::string direct_variable = ((direct_variable_c *)(((location_c *)located_var_decl->location)->direct_variable))->value;
//
//                    //SYM_REF2(simple_spec_init_c, simple_specification, constant)
//                    simple_spec_init_c *located_var_spec_init = (simple_spec_init_c *)located_var_decl->located_var_spec_init;
//
//                    std::string simple_specification = ST_parser::parse(located_var_spec_init->simple_specification);
//
//                    /*
//                     * parse the initial value of the variable
//                    */
//                    std::string constant = "";
//                    if (located_var_spec_init->constant != 0)
//                    {
//                        constant = ST_parser::parse(located_var_spec_init->constant);
//                    }
//
//                    Var *new_var = new Var(variable_name, simple_specification, Var::SEMANTICS_LOCATED);
//                    new_var->set_str_constant(constant);
//
//                    var_list.push_back(new_var);
//                }
//            }
//            else
//            {
//                //SYM_LIST(located_var_decl_list_c)
//                located_var_decl_list_c *located_var_decl_list = (located_var_decl_list_c *)located_var_declarations->located_var_decl_list;
//
//                int nn = located_var_decl_list->n;
//                for (int j = 0; j < nn; j++)
//                {
//                    //SYM_REF3(located_var_decl_c, variable_name, location, located_var_spec_init)
//                    located_var_decl_c *located_var_decl = (located_var_decl_c *) located_var_decl_list->get_element(j);
//
//                    //SYM_TOKEN(identifier_c)
//                    std::string variable_name = ((identifier_c *)located_var_decl->variable_name)->value;
//
//                    //SYM_REF1(location_c, direct_variable)
//                    std::string direct_variable = ((direct_variable_c *)(((location_c *)located_var_decl->location)->direct_variable))->value;
//
//                    //SYM_REF2(simple_spec_init_c, simple_specification, constant)
//                    simple_spec_init_c *located_var_spec_init = (simple_spec_init_c *)located_var_decl->located_var_spec_init;
//
//                    std::string simple_specification = ST_parser::parse(located_var_spec_init->simple_specification);
//
//                    std::string constant = "";
//                    if (located_var_spec_init->constant != 0)
//                    {
//                        constant = ST_parser::parse(located_var_spec_init->constant);
//                    }
//
//                    Var *new_var = new Var(variable_name, simple_specification, Var::SEMANTICS_LOCATED);
//                    new_var->set_str_constant(constant);
//
//                    var_list.push_back(new_var);
//                }
//            }
        }
            //SYM_REF2(external_var_declarations_c, option, external_declaration_list)
        else if (cname.compare("external_var_declarations_c") == 0)
        {

        }
            //SYM_REF2(global_var_declarations_c, option, global_var_decl_list)
        else if (cname.compare("global_var_declarations_c") == 0)
        {

        }
            //SYM_REF2(incompl_located_var_declarations_c, option, incompl_located_var_decl_list)
        else if (cname.compare("incompl_located_var_declarations_c") == 0)
        {

        }
    }

    ret->set_var_list(var_list);

    return ret;
}


/**
* private attributes and methods
*/
CFG_builder *CFG_builder::builder = 0;

CFG_builder::CFG_builder()
{
}

