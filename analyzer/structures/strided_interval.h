#ifndef STRIDED_INTERVAL_H
#define STRIDED_INTERVAL_H

#include "abstract_data.h"

class Strided_interval : public Abstract_data
{
    /**
    * public static methods
    */
public:
    static Strided_interval *get_top();

    static Strided_interval *get_bot();

    static Strided_interval *get_singleton_set(int);

    static Strided_interval *get_interval(int, int);

    static Strided_interval *get_strided_interval(int, int, int);

    static Strided_interval *get_strided_interval(std::vector<int> );


    /**
    * public methods
    */
    virtual ~Strided_interval();


    /**
    * operations
    */
    Strided_interval *Add(int);

    Strided_interval *Add(Strided_interval *);

    Strided_interval *Sub(int);

    Strided_interval *Sub(Strided_interval *);

    Strided_interval *Union(Strided_interval *);

    Strided_interval *Intersect(Strided_interval *);

    Strided_interval *remove_lower_bound();

    Strided_interval *remove_upper_bound();

    Strided_interval *Negate();

    Strided_interval *Or(Strided_interval *);

    Strided_interval *Not();

    Strided_interval *And(Strided_interval *);

    Strided_interval *Xor(Strided_interval *);

    Boolean4 *Compare(Strided_interval *);

    Boolean4 *Smaller(Strided_interval *);

    Strided_interval *Except(Strided_interval *);

    Strided_interval *Widen(Strided_interval *);

    Strided_interval *Extend();

    Strided_interval *sign_extend();

    Boolean4 *Greater(Strided_interval *);

    Boolean4 *greater_or_equal(Strided_interval *);

    Boolean4 *smaller_or_equal(Strided_interval *);

    std::vector<int> si_to_array();


    /**
    * getters and setters
    */
    int get_lower();

    void set_lower(int);

    int get_upper();

    void set_upper(int);

    int get_stride();

    void set_stride(int);


    /**
    * inherited methods (helpers)
    */
    bool equal(Abstract_data *);

    std::ostream &print(std::ostream &);

    bool is_singleton_set();

    bool is_top();

    bool is_bot();

    bool is_zero();

    bool is_one();

    bool is_interval();

    bool contains(int);

    bool contains(Strided_interval *);

    bool is_lower_bound_minimal();

    bool is_upper_bound_maximal();

    int shared_suffix_mask();

    int shared_prefix_mask();


    /**
    * helpers - debug only
    */
    std::string to_string();



    /**
    * private attributes and methods
    */
private:
    int lower, upper, stride;

    Strided_interval(int, int, int);
};

#endif // STRIDED_INTERVAL_H
