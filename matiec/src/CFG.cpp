#include <iostream>
#include <typeinfo>

#include "CFG.h"


using std::cout;
using std::endl;

Node::Node(string _name)
{
    this->name = _name;
    if (this->name.find("start") != this->name.npos)
    {
        this->type = START;
    } else if (this->name.find("end") != this->name.npos)
    {
        this->type = END;
    } else
    {
        this->type = WRONG_NODE_TYPE;
        cout << "In building a Node: pass a wrong name." << endl;
    }
}
Node::Node(symbol_c *_statement)
{
    this->statement = _statement;

    string str_type = this->statement->absyntax_cname();

    if (str_type.compare("assignment_statement_c") == 0)
    {
        this->type = ASSIGNMENT;

    } else if (str_type.compare("return_statement_c") == 0)
    {
        this->type = RETURN;
    } else if (str_type.compare("fb_invocation_c") == 0)
    {
        this->type = FB_INVOCATION;
    } else if (str_type.compare("if_statement_c") == 0)
    {
        this->type = IF;
    } else if (str_type.compare("elseif_statement_list_c") == 0)
    {
        this->type = ELSEIF_LIST;
    } else if (str_type.compare("elseif_statement_c") ==0 )
    {
        this->type = ELSEIF;
    } else if (str_type.compare("case_statement_c") == 0)
    {
        this->type = CASE;
    } else if (str_type.compare("case_element_list_c") == 0)
    {
        this->type = CASE_ELEMENT_LIST;
    } else if (str_type.compare("case_element_c") == 0)
    {
        this->type = CASE_ELEMENT;
    } else if (str_type.compare("for_statement_c") == 0)
    {
        this->type = FOR;
    } else if (str_type.compare("while_statement_c") == 0)
    {
        this->type = WHILE;
    } else if (str_type.compare("repeat_statement_c") == 0)
    {
        this->type = REPEAT;
    } else if (str_type.compare("exit_statement_c") == 0)
    {
        this->type = EXIT;
    } else
    {
        cout << "In building a Node: pass a wrong type of statement!" << endl;
    }
}

Node::~Node()
{

}


CFG::CFG(symbol_c *_pou)
{
    this->pou = _pou;
    string str_type = _pou->absyntax_cname();
    if (str_type.compare("function_declaration_c") == 0)
    {
        string str_name = ((function_declaration_c *)_pou)->derived_function_name->token->value;
        this->name = str_name;
        this->type = FUNCTION;
        this->stmt_list = (statement_list_c *)((function_declaration_c *)_pou)->function_body;

    } else if (str_type.compare("function_block_declaration_c") == 0)
    {
        string str_name = ((function_block_declaration_c *)_pou)->fblock_name->token->value;
        this->name = str_name;
        this->type = FUNCTION_BLOCK;
        this->stmt_list = (statement_list_c *)((function_block_declaration_c *)_pou)->fblock_body;
    }
    else if (str_type.compare("program_declaration_c") == 0)
    {
        string str_name = ((program_declaration_c *)_pou)->program_type_name->token->value;
        this->name = str_name;
        this->type = PROGRAM;
        this->stmt_list = (statement_list_c *)((program_declaration_c *)_pou)->function_block_body;
    }
    else
    {
        cout << "In building CFG: pass a wrong type of pou!" << endl;
    }
}

CFG::~CFG()
{
    //dtor
}

void CFG::init_CFG()
{
    Node *_start = new Node( this->name + "_start");

    int n = this->stmt_list->n;
    Node *node = 0;
    Node *pre = _start;

    for (int i=0; i<n; i++)
    {
        node = new Node(this->stmt_list->get_element(i));
        pre->successors.push_back(node);
        pre = node;
    }
    pre->successors.push_back(new Node( this->name + "_end"));

    this->start = _start;
}

void CFG::print_CFG()
{
    Node *current = this->start;

    while(current !=0 )
    {
        cout << current->name << " " << current->type << endl;
        if(current->successors.size() > 0)
            current = current->successors[0];
        else
            break;
    }

}
void CFG::refine_CFG()
{

}
