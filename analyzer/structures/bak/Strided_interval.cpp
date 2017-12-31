#include "Strided_interval.h"

/**
* static attributes
*/
//top : 1[min, max]
Strided_interval *Strided_interval::top()
{
    static Strided_interval *ELEM_TOP = new Strided_interval(1, INT_MIN, INT_MAX);
    return ELEM_TOP;
}
//bot : -1[0, 0]
Strided_interval *Strided_interval::bot()
{
    static Strided_interval *ELEM_BOT = new Strided_interval();
    return ELEM_BOT;
}

/**
* public methods
*/
Strided_interval::Strided_interval()
{
    stride = -1;
    low = 0;
    high = 0;
}
Strided_interval::Strided_interval(int x)
{
    stride = 0;
    low = x;
    high = x;
}
Strided_interval::Strided_interval(int _stride, int _low, int _high)
{
    stride = _stride;
    low = _low;
    high = _high;
}
Strided_interval::Strided_interval(Strided_interval *si)
{
    stride = si->get_stride();
    low = si->get_low();
    high = si->get_high();
}
Strided_interval::~Strided_interval()
{
}
Strided_interval *Strided_interval::Join(Strided_interval *rhs)
{
    //union of two intervals
    if (this == top() || rhs == top())
    {
        return new Strided_interval(1, INT_MIN, INT_MAX);
    }
    if (stride < 0 && rhs->get_stride() < 0)
    {
        return new Strided_interval();
    }
    else if (stride < 0)
    {
        return rhs;
    }
    else if (rhs->get_stride() < 0)
    {
        return this;
    }
    else
    {
        std::set<int> values;
        values.insert(low);
        values.insert(high);
        values.insert(rhs->get_low());
        values.insert(rhs->get_high());

        if(values.size() != 1)
        {
            int new_stride = utils::gcd(stride, rhs->get_stride());
            std::set<int>::iterator cur, next;
            for (cur = values.begin(), next = values.begin(), ++next; next != values.end(); ++cur, ++next)
            {
                new_stride = utils::gcd(new_stride, *next - *cur);
            }
            int new_low = *(values.begin());
            int new_high = *cur;
            return new Strided_interval(new_stride, new_low, new_high);
        }
    }
}
void Strided_interval::Neg()
{
    if (stride < 0)
    {
        return;
    }
    int tmp_low = low;
    low = -high;
    high = -tmp_low;
}
void Strided_interval::Not()
{
    if (stride < 0)
    {
        return;
    }
    int tmp_low = low;
    low = -high - 1;
    high = -tmp_low - 1;
}

Strided_interval *Strided_interval::Add(Strided_interval *rhs)
{
    if (stride < 0 || rhs->get_stride() < 0)
    {
        return new Strided_interval();
    }
    if (this == top() || rhs == top())
    {
        return new Strided_interval(1, INT_MIN, INT_MAX);
    }
    int new_stride = utils::gcd(stride, rhs->get_stride());
    int new_low = low + rhs->get_low();
    int new_high = high + rhs->get_high();

    if (low > high)
    {
        return new Strided_interval(1, INT_MIN, INT_MAX);
    }
    return new Strided_interval(new_stride, new_low, new_high);
}

Strided_interval *Strided_interval::Sub(Strided_interval *rhs)
{
    Strided_interval *neg(rhs);
    neg->Neg();
    return this->Add(neg);

}
Strided_interval *Strided_interval::Intersection(Strided_interval *rhs)
{
    if (stride == 0)
    {
        if(rhs->get_stride() == 0)
        {
            if (low != rhs->get_low())
            {
                return new Strided_interval();
            }
            else
            {
                return new Strided_interval(low);
            }
        }
        else
        {
            if (low < rhs->get_low() || low > rhs->get_high() || (low - rhs->get_low()) % rhs->get_stride() !=0 )
            {
                return new Strided_interval();
            }
            else
            {
                return new Strided_interval(rhs);
            }
        }
    }
    else
    {
        if (rhs->get_stride() == 0)
        {
            if (low > rhs->get_low() || high < rhs->get_low() || ((rhs->get_low() - low) % stride != 0))
            {
                return new Strided_interval();
            }
            else
            {
                return new Strided_interval(rhs);
            }
        }
        else
        {
            int new_stride = utils::gcd(stride, rhs->get_stride());
            if (low > rhs->get_high() || high < rhs->get_low() || (low - rhs->get_low()) % new_stride != 0)
            {
                return new Strided_interval();
            }
            else
            {
                int x, k1, k2;
                utils::extend_euclidean(stride/new_stride, rhs->get_stride() / new_stride, k1, k2);
                x = (low - rhs->get_low()) / new_stride;

                k1 *= x;
                k2 *= -x;

                new_stride = stride * rhs->get_stride() / utils::gcd(stride, rhs->get_stride());
                int new_low = low + k1 * stride, new_high = high;

                if (new_low < low)
                {
                    new_low += ((low - new_low - 1) / new_stride + 1) * new_stride;
                }
                if (new_low < rhs->get_low())
                {
                    new_low += ((rhs->get_low() - new_low - 1) / new_stride + 1) * new_stride;
                }
                if (rhs->get_high() < new_high)
                {
                    new_high = rhs->get_high();
                }
                if (new_high < new_low)
                {
                    return new Strided_interval();
                }
                else
                {
                    new_high -= (new_high - new_low) % new_stride;
                    return new Strided_interval(new_stride, new_low, new_high);
                }
            }
        }
    }
}


/**
* getters and setters
*/
int Strided_interval::get_stride()
{
    return stride;
}
int Strided_interval::get_low()
{
    return low;
}
int Strided_interval::get_high()
{
    return high;
}

/**
* helpers
*/

Strided_interval *Strided_interval::operator =(Strided_interval *rhs)
{
    stride = rhs->get_stride();
    low = rhs->get_low();
    high = rhs->get_high();
    return this;
}
bool Strided_interval::operator ==(Strided_interval *rhs) const
{
    if (stride != rhs->get_stride())
    {
        return false;
    }
    if (low != rhs->get_low())
    {
        return false;
    }
    if (high != rhs->get_high())
    {
        return false;
    }
    return true;
}
bool Strided_interval::operator !=(Strided_interval *rhs) const
{
    return !(this==rhs);
}
std::string Strided_interval::format()
{
    std::stringstream o;
    o << stride << "[" << low << "," << high << "]";
    return o.str();
}
void Strided_interval::print(std::ostream &out)
{
    out << this->format();
}
