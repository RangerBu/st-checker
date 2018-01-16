#ifndef CTS_H
#define CTS_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include <ostream>

#include "../../flow-graph-builder/Node.h"
#include "../../../analyzer/domain/value_set.h"
#include "program_state.h"
#include "transition_rule.h"

typedef std::set<std::string> alphabet;
typedef std::map<std::string, Transition_rule *> rules_map;

class CTS
{
    /**
    * public methods
    */
public:
    CTS();

    virtual ~CTS();


    /**
    * getters and setters
    */
    std::vector<int> get_T_list();

    void set_T_list(std::vector<int> );

    std::set<Program_state *> get_S_set();

    void set_S_set(std::set<Program_state *>);

    int get_t_0();

    void set_t_0(int);

    Program_state *get_s_0();

    void set_s_0(Program_state *);

    alphabet get_sigma();

    void set_sigma(alphabet);

    rules_map get_nabla();

    void set_nabla(rules_map);


    /**
    * helpers
    */
    std::ostream &print(std::ostream &);

    std::ostream &print_dot(std::ostream &);


    /**
    * helpers - debug only
    */
    std::string to_string();



    /**
    * private attributes
    */
private:
    /*
    * the vector of cycles
    */
    std::vector<int> T_list;

    /*
    * the set of program states
    */
    std::set<Program_state *> S_set;

    /*
    * the initial cycle
    */
    int t_0;

    /*
    * the initial program state
    */
    Program_state *s_0;

    /*
    * the alphabet of labels
    */
    std::set<std::string> sigma;

    /*
    * the set of transition rules
    * the rule name like 'r1' and the corresponding rule program_state -> program_state
    */
    rules_map nabla;


};

#endif // CTS_H
