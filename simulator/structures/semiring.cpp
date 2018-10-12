//
// Created by Samson on 2018/6/1.
//

#include "../../debug_helper.h"
#include "semiring.h"
wali::sem_elem_t Semiring::get_one()
{
    return ELEM_ONE;
}

wali::sem_elem_t Semiring::get_zero()
{
    return ELEM_ZERO;
}

Semiring::Semiring(symbol_c *_symbol) : symbol(_symbol)
{
    if (v_values.size() != 0)
    {
        Debug_helper::print_debug_info(__FILE__, __LINE__, "在以symbol作为参数创建Semiring对象时，发生了错误，v_values.size() != 0");
        exit(233);
    }
}

Semiring::Semiring(std::vector<Configuration *> _v_values) : v_values(_v_values)
{
    symbol = 0;
}
Semiring::~Semiring()
{
}

wali::sem_elem_t Semiring::one() const
{
    return ELEM_ONE;
}

wali::sem_elem_t Semiring::zero() const
{
    return ELEM_ZERO;
}

wali::sem_elem_t Semiring::extend(wali::SemElem *_other)
{

}

wali::sem_elem_t Semiring::combine(wali::SemElem *_other)
{

}

bool Semiring::equal(wali::SemElem *_other) const
{
    Semiring *other = static_cast<Semiring *>(_other);

    // 存在一方symbol != 0时
    if (symbol != 0 || other->get_symbol() != 0)
    {
        return symbol == other->get_symbol();
    }

    // 双方symbol都为0
    if (v_values.size() > 0 || other->get_v_values().size() > 0)
    {
        if (v_values.size() != other->get_v_values().size())
        {
            return false;
        }
        bool flag;
        for (int i = 0; i < v_values.size(); ++i)
        {
            flag = false;
            for (int j = 0; j < other->get_v_values().size(); ++j)
            {
                if (v_values[i] == other->get_v_values()[j])
                {
                    flag = true;
                }
            }
            if (!flag)
            {
                return false;
            }
        }
        return true;
    }

    // symbol == 0 && v_value.size() == 0

    return this == other;
}

std::ostream& Semiring::print(std::ostream &_out) const
{

}

/**
 * getters and setters
 */
symbol_c* Semiring::get_symbol()
{
    return symbol;
}

std::vector<Configuration *> Semiring::get_v_values()
{
    return v_values;
}

Semiring *Semiring::ELEM_ONE = new Semiring(0);

Semiring *Semiring::ELEM_ZERO = new Semiring(0);