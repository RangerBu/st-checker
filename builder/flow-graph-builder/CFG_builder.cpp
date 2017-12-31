#include "CFG_builder.h"

/**
* public methods
*/
CFG_builder::CFG_builder()
{
    parser = new ST_parser();
}
CFG_builder::CFG_builder(ST_parser *_parser)
{
    parser = _parser;
}
CFG_builder::~CFG_builder()
{
}

CFG *CFG_builder::create()
{
    CFG *ret = new CFG(parser->get_stmts_list());
    init_vars();
    ret->set_vars(vars);
    return ret;
}

/**
* getters and setters
*/
std::vector<Var *> CFG_builder::get_vars()
{
    return vars;
}

/**
* private methods
*/
void CFG_builder::init_vars()
{
    var_declarations_list_c *var_decls = parser->get_vars();
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

                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    /* str_name */
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    vars.push_back(new Var(name, Var::get_int_type(simple_specification), Var::get_int_semantic("INPUT")));
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

                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    /* str_name */
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    vars.push_back(new Var(name, Var::get_int_type(simple_specification), Var::get_int_semantic("OUTPUT")));
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

                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    vars.push_back(new Var(name, Var::get_int_type(simple_specification), Var::get_int_semantic("VAR")));
                }
            }
        }
        //SYM_REF1(retentive_var_declarations_c, var_init_decl_list)
        else if (cname.compare("retentive_var_declarations_c") == 0)
        {
            retentive_var_declarations_c *var_decl_list = (retentive_var_declarations_c *)elem;
            //SYM_LIST(var_init_decl_list_c)
            var_init_decl_list_c *var_init_decl_list = (var_init_decl_list_c *)var_decl_list->var_init_decl_list;
            int nn = var_init_decl_list->n;

            for (int j = 0; j < nn; j++)
            {
                //SYM_REF2(var1_init_decl_c, var1_list, spec_init)
                var1_init_decl_c *var1_init_decl = (var1_init_decl_c *)var_init_decl_list->get_element(j);
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
                int nnn = var1_list->n;
                for (int k = 0; k < nnn; k++)
                {
                    std::string name = ST_parser::parse(var1_list->get_element(k));

                    vars.push_back(new Var(name, Var::get_int_type(simple_specification), Var::get_int_semantic("RETENTIVE")));
                }
            }
        }
        //SYM_REF2(located_var_declarations_c, option, located_var_decl_list)
        else if (cname.compare("located_var_declarations_c") == 0)
        {
            located_var_declarations_c *located_var_declarations = (located_var_declarations_c *)elem;
            if (located_var_declarations->option != 0)
            {
                //SYM_LIST(located_var_decl_list_c)
                located_var_decl_list_c *located_var_decl_list = (located_var_decl_list_c *)located_var_declarations->located_var_decl_list;

                int nn = located_var_decl_list->n;
                for (int j = 0; j < nn; j++)
                {
                    //SYM_REF3(located_var_decl_c, variable_name, location, located_var_spec_init)
                    located_var_decl_c *located_var_decl = (located_var_decl_c *) located_var_decl_list->get_element(j);

                    //SYM_TOKEN(identifier_c)
                    std::string variable_name = ((identifier_c *)located_var_decl->variable_name)->value;

                    //SYM_REF1(location_c, direct_variable)
                    std::string direct_variable = ((direct_variable_c *)(((location_c *)located_var_decl->location)->direct_variable))->value;

                    //SYM_REF2(simple_spec_init_c, simple_specification, constant)
                    simple_spec_init_c *located_var_spec_init = (simple_spec_init_c *)located_var_decl->located_var_spec_init;

                    std::string simple_specification = ST_parser::parse(located_var_spec_init->simple_specification);

                    std::string constant = "";
                    if (located_var_spec_init->constant != 0)
                    {
                        constant = ST_parser::parse(located_var_spec_init->constant);
                    }

                    vars.push_back(new Var(variable_name, Var::get_int_type(simple_specification), Var::get_int_semantic("LOCATED")));
                }
            }
            else
            {
                //SYM_LIST(located_var_decl_list_c)
                located_var_decl_list_c *located_var_decl_list = (located_var_decl_list_c *)located_var_declarations->located_var_decl_list;

                int nn = located_var_decl_list->n;
                for (int j = 0; j < nn; j++)
                {
                    //SYM_REF3(located_var_decl_c, variable_name, location, located_var_spec_init)
                    located_var_decl_c *located_var_decl = (located_var_decl_c *) located_var_decl_list->get_element(j);

                    //SYM_TOKEN(identifier_c)
                    std::string variable_name = ((identifier_c *)located_var_decl->variable_name)->value;

                    //SYM_REF1(location_c, direct_variable)
                    std::string direct_variable = ((direct_variable_c *)(((location_c *)located_var_decl->location)->direct_variable))->value;

                    //SYM_REF2(simple_spec_init_c, simple_specification, constant)
                    simple_spec_init_c *located_var_spec_init = (simple_spec_init_c *)located_var_decl->located_var_spec_init;

                    std::string simple_specification = ST_parser::parse(located_var_spec_init->simple_specification);

                    std::string constant = "";
                    if (located_var_spec_init->constant != 0)
                    {
                        constant = ST_parser::parse(located_var_spec_init->constant);
                    }
                    vars.push_back(new Var(variable_name, Var::get_int_type(simple_specification), Var::get_int_semantic("LOCATED")));
                }
            }
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
}
