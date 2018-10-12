//
// Created by Samson on 2018/6/1.
//

#ifndef VERIFY_ST_PROGRAMS_SEMIRING_H
#define VERIFY_ST_PROGRAMS_SEMIRING_H

#include <map>

#include "wali/SemElem.hpp"
#include "absyntax/absyntax.hh"

#include "configuration.h"

class Semiring : public wali::SemElem
{
public:
    static wali::sem_elem_t get_one();

    static wali::sem_elem_t get_zero();

public:
    Semiring(symbol_c *_symbol);

    Semiring(std::vector<Configuration *> _v_values);

    virtual ~Semiring();

    wali::sem_elem_t one() const;

    wali::sem_elem_t zero() const;

    wali::sem_elem_t extend(wali::SemElem *_other);

    wali::sem_elem_t combine(wali::SemElem *_other);

    bool equal(wali::SemElem *_other) const;

    std::ostream &print(std::ostream &_out) const;

    /**
     * getters and setters
     */
    symbol_c *get_symbol();

    std::vector<Configuration *> get_v_values();

private:

    static Semiring *ELEM_ONE;

    static Semiring *ELEM_ZERO;

    /**
     * 1. symbol != 0 && values.size() == 0，使用ICFG中边创建的对象
     * 2. symbol == 0 && values.size() > 0时，说明当前对象为通过extend，或combine操作计算得到的
     * 3. symbol == 0 && values.size() == 0, zero 和 one
     */

    // 抽象语法树中的符号
    symbol_c *symbol;

    // 包含configuration的集合
    std::vector<Configuration *> v_values;

};


#endif //VERIFY_ST_PROGRAMS_SEMIRING_H
