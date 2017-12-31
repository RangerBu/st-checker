#include "Strided_interval.h"

/**
* pre-declarations
*/
//unsigned int_to_unsigned(int x);
//int unsigned_to_int(unsigned x);
int number_of_trailing_zeros(int i);
int number_of_leading_zeros(int i);
/**
* public static methods
*/
Strided_interval *Strided_interval::get_top()
{
    if (ELEM_TOP == 0)
    {
        ELEM_TOP = new Strided_interval(1, (1 << (width->get_width() - 1)), ((1 << (width->get_width() - 1)) - 1));
    }
    return ELEM_TOP;
}
Strided_interval *Strided_interval::get_bot()
{
    if (ELEM_BOT == 0)
    {
        ELEM_BOT = new Strided_interval(-1, 0, 0);
    }
    return ELEM_BOT;
}
Strided_interval *Strided_interval::get_singleton_set(int _num)
{
    return get_strided_interval(0, _num, _num);
}
Strided_interval *Strided_interval::get_interval(int _lower, int _upper)
{
    return get_strided_interval(1, _lower, _upper);
}
Strided_interval *Strided_interval::get_strided_interval(int _stride, int _lower, int _upper)
{
    return new Strided_interval(_stride, _lower, _upper);
}
Strided_interval *Strided_interval::get_strided_interval(std::vector<int> _array)
{
    if (_array.size() == 0)
    {
        return Strided_interval::get_bot();
    }
    int max_value = 1 << 31;
    int min_value = (1<<31) -1;

    for (int i=0; i<_array.size(); i++)
    {
        if (_array[i] > max_value)
        {
            max_value = _array[i];
        }

        if (_array[i] < min_value)
        {
            min_value = _array[i];
        }
    }
    int new_stride = max_value - min_value;

    int i = new_stride, j = 0;
    for (; i>1; i--)
    {
        for (; j<_array.size(); j++)
        {
            if ((_array[j] - min_value) % i != 0)
            {
                break;
            }
        }
        if (j == _array.size())
        {
            break;
        }
    }
    return Strided_interval::get_strided_interval(i, min_value, max_value);
}

/**
* private static attributes and methods
*/
Strided_interval *Strided_interval::ELEM_BOT = 0;
Strided_interval *Strided_interval::ELEM_TOP = 0;
Data_width *Strided_interval::width = Data_width::get_instance(32);

int Strided_interval::gcd(int _a, int _b)
{
    if (_b == 0)
    {
        return _a;
    }
    return gcd(_b, _a % _b);
}
int *Strided_interval::extended_gcd(int _a, int _b)
{
    if (_b == 0)
    {
        return new int[3]{_a, 1, 0};
    }
    int *ans = extended_gcd(_b, _a % _b);
    return new int [3] {ans[0], ans[2], ans[1] - ((_a % _b) * ans[2])};
}
unsigned Strided_interval::min_or(unsigned _a, unsigned _b, unsigned _c, unsigned _d)
{
    unsigned m, tmp;
    m = 1 << (width->get_width() - 1);
    while (m != 0)
    {
        if ((~_a & _c & m) != 0)
        {
            tmp = (_a | m) & -m;
            if (tmp <= _b)
            {
                _a = tmp;
                break;
            }
        }
        else if ( (_a & ~_c & m) != 0)
        {
            tmp = (_c | m) & -m;
            if (tmp <= _d)
            {
                _c = tmp;
                break;
            }
        }
        m = m >> 1;
    }
    return _a | _c;
}
unsigned Strided_interval::max_or(unsigned _a, unsigned _b, unsigned _c, unsigned _d)
{
    unsigned m, tmp;
    m = 1 << (width->get_width() - 1);
    while (m != 0)
    {
        if ((_b & _d &m) != 0)
        {
            tmp = (_b - m) | (m - 1);
            if (tmp >= _a)
            {
                _b = tmp;
                break;
            }
            tmp = (_d - m) | (m - 1);
            if (tmp >= _c)
            {
                _d = tmp;
                break;
            }

        }
        m = m >> 1;
    }
    return _b | _d;
}
int Strided_interval::min_or_signed(int _a, int _b, int _c, int _d)
{
    unsigned m = 1 << 31;
    if ((_a & _b & _c & _d & m) != 0)
    {
        return min_or(_a, _b, _c, _d);
    }
    else if ((_a & _b & _c & ~_d & m) != 0)
    {
        return _a;
    }
    else if ( (_a & _b & ~_c & ~_d & m) != 0)
    {
        return min_or(_a, _b, _c, _d);
    }
    else if ((_a & ~_b & _c & _d & m) != 0)
    {
        return _c;
    }
    else if ((_a & ~_b & _c & ~_d & m) != 0)
    {
        return _a < _c ? _a : _c;
    }
    else if ((_a & ~_b & ~_c & ~_d & m) != 0)
    {
        return min_or(_a, -1, _c, _d);
    }
    else if ((~_a & ~_b & _c & _d & m) != 0)
    {
        return min_or(_a, _b, _c, _d);
    }
    else if ((~_a & ~_b & _c & ~_d & m) != 0)
    {
        return min_or(_a, _b, _c, -1);
    }
    else if ((~_a & ~_b & ~_c & ~_d & m) != 0)
    {
        return min_or(_a, _b, _c, _d);
    }
}
int Strided_interval::max_or_signed(int _a, int _b, int _c, int _d)
{
    unsigned m = 1 << 31;
    if ((_a & _b & _c & _d & m) != 0)
    {
        return max_or(_a, _b, _c, _d);
    }
    else if ((_a & _b & _c & ~_d & m) != 0)
    {
        return -1;
    }
    else if ((_a & _b & ~_c & ~_d & m) != 0)
    {
        return max_or(_a, _b, _c, _d);
    }
    else if ((_a & ~_b & _c & _d & m) != 0)
    {
        return -1;
    }
    else if ((_a & ~_b & _c & ~_d & m) != 0)
    {
        return max_or(0, _b, 0, _d);
    }
    else if ((_a & ~_b & ~_c & ~_d & m) != 0)
    {
        return max_or(0, _b, _c, _d);
    }
    else if ((~_a & ~_b & _c & _d & m) != 0)
    {
        return max_or(_a, _b, _c, _d);
    }
    else if ((~_a & ~_b & _c & ~_d & m) != 0)
    {
        return max_or(_a, _b, 0, _d);
    }
    else if ((~_a & ~_b & ~_c & ~_d & m) != 0)
    {
        return max_or(_a, _b, _c, _d);
    }
}

/**
* public methods
*/
Strided_interval::~Strided_interval()
{
}

Strided_interval *Strided_interval::Add(int _num)
{
    return Add(get_singleton_set(_num));
}
Strided_interval *Strided_interval::Add(Strided_interval *_si)
{
    if (_si->equals(Strided_interval::get_bot()))
    {
        return this;
    }
    if (equals(Strided_interval::get_bot()))
    {
        return _si;
    }

    int new_stride = gcd(stride, _si->get_stride());
    int new_lower = lower + _si->get_lower();
    int new_upper = upper + _si->get_upper();

    int u = lower & _si->get_lower() & ~lower & ~(upper & _si->get_upper() & ~new_upper);
    int v = ((lower ^ _si->get_lower()) | ~(lower ^ new_lower)) & (~upper & ~_si->get_upper() & new_upper);

    u = width->effective_value(u);
    v = width->effective_value(v);
    if ((u | v) < 0)
    {
        return get_top();
    }
    else
    {
        return get_strided_interval(new_stride, width->effective_value(new_lower), width->effective_value(new_upper));
    }
}
Strided_interval *Strided_interval::Sub(int _num)
{
    return Add(-_num);
}
Strided_interval *Strided_interval::Sub(Strided_interval *_si)
{
    return Add(_si->Negate());
}
Strided_interval *Strided_interval::Union(Strided_interval *_si)
{
    if (this->equals(Strided_interval::get_bot()))
    {
        return _si;
    }
    if (_si->equals(Strided_interval::get_bot()))
    {
        return this;
    }

    if (upper > _si->get_upper())
    {
        return _si->Union(this);
    }

    int new_lower = lower < _si->get_lower() ? lower : _si->get_lower();
    int new_upper = upper > _si->get_upper() ? upper : _si->get_upper();
    int delta = 0;

    if (upper <= _si->get_lower())
    {
        delta = _si->get_lower() - upper;
    }
    else if (lower < _si->get_lower() && upper < _si->get_upper())
    {
        delta = upper - _si->get_lower();
    }
    else
    {
        delta = lower - _si->get_lower();
    }

    int i_gcd = gcd(gcd(stride, _si->get_stride()), delta);
    int new_stride = i_gcd < 0 ? -i_gcd : i_gcd;
    return get_strided_interval(new_stride, new_lower, new_upper);
}
Strided_interval *Strided_interval::Intersect(Strided_interval *_si)
{
    if (equals(Strided_interval::get_bot()) || _si->equals(Strided_interval::get_bot()))
    {
        return Strided_interval::get_bot();
    }
    if (is_singleton_set())
    {
        if (lower >= _si->get_lower() && lower <= _si->get_upper())
        {
            return this;
        }
        else
        {
            return get_bot();
        }
    }
    else if (_si->is_singleton_set())
    {
        if (_si->get_lower() >= lower && _si->get_upper() <= upper)
        {
            return _si;
        }
        else
        {
            return get_bot();
        }
    }
    if (upper > _si->get_upper())
    {
        return _si->Intersect(this);
    }

    if (upper <= _si->get_lower())
    {
        return get_bot();
    }
    else
    {
        int *ans = extended_gcd(_si->get_stride(), stride);
        int i_gcd = ans[0];
        int u = ans[1];
        int v = ans[2];

        long diff = (long)upper - _si->get_lower();
        long new_stride = (stride * _si->get_stride()) / i_gcd;

        if ((diff % i_gcd) != 0)
        {
            return get_bot();
        }

        long i0 = (diff / i_gcd) * u;
        long j0 = (diff / i_gcd) * v;
        long anchor = _si->get_lower() + (i0 * _si->get_stride());

        if (!(anchor == (upper - (j0 * stride))))
        {
            std::cout << "Anchor is invalid" << std::endl;
        }

        int tmp = lower > _si->get_lower() ? lower : _si->get_lower();
        long t = (tmp - anchor) / new_stride;
        if (t >= 0 && ((tmp - anchor) % new_stride) != 0)
        {
            t++;
        }

        int new_lower = anchor + (t * new_stride);
        tmp = upper < _si->get_upper() ? upper : _si->get_upper();
        if (new_lower > tmp)
        {
            return get_bot();
        }
        else if (tmp - (long)new_lower < new_stride)
        {
            return get_singleton_set(new_lower);
        }
        else
        {
            int s = (tmp - new_lower) / new_stride + 1;
            return get_strided_interval(new_stride, new_lower, new_lower + (s - 1) * new_stride);
        }

    }
}
Strided_interval *Strided_interval::remove_lower_bound()
{
    if (lower == width->get_minimum_value())
    {
        return this;
    }
    else if (is_singleton_set())
    {
        return get_strided_interval(1, width->get_minimum_value(), upper);
    }
    else
    {
        int new_lower = width->get_minimum_value();

        long tmp = upper - new_lower;
        int delta = (int)(upper % stride);
        new_lower += delta;

        return get_strided_interval(stride, new_lower, upper);
    }
}
Strided_interval *Strided_interval::remove_upper_bound()
{
    if (upper == width->get_maximum_value())
    {
        return this;
    }
    else if (is_singleton_set())
    {
        return get_strided_interval(1, lower, width->get_maximum_value());
    }
    else
    {
        int new_upper = width->get_maximum_value();
        long tmp = new_upper - lower;
        int delta = (int)(upper % stride);

        new_upper -= delta;
        return get_strided_interval(stride, lower, new_upper);
    }

}
Strided_interval *Strided_interval::Negate()
{
    if (is_singleton_set() && is_lower_bound_minimal())
    {
        return this;
    }
    else if (!is_lower_bound_minimal())
    {
        return get_strided_interval(stride, -upper, -lower);
    }
    else
    {
        return get_top();
    }
}
Strided_interval *Strided_interval::Or(Strided_interval *_si)
{
    int suffix_mask_1 = shared_suffix_mask();
    int suffix_mask_2 = _si->shared_prefix_mask();
    int suffix_bits_1 = suffix_mask_1 & lower;
    int suffix_bits_2 = suffix_mask_2 & _si->get_lower();
    int suffix_bits = suffix_bits_1 | suffix_bits_2;

    int t1 = number_of_trailing_zeros(stride);
    int t2 = number_of_trailing_zeros(_si->get_stride());
    int t = t1 < t2 ? t1 : t2;
    int mask = (1 << t) - 1;

    int new_stride = 1 << t;
    int new_shared_suffix = (lower & mask) | (_si->get_lower() & mask);

    int new_lower = min_or_signed((lower & ~mask), (upper & ~mask), (_si->get_lower() & ~mask), (_si->get_upper() & ~mask));
    int new_upper = max_or_signed((lower & ~mask), (upper & ~mask), (_si->get_lower() & ~mask), (_si->get_upper() & ~mask));

    new_lower = (new_lower & ~mask) | new_shared_suffix;
    new_upper = (new_upper & ~mask) | new_shared_suffix;

    while((new_lower & suffix_bits) != suffix_bits) new_lower++;
    while((new_upper & suffix_bits) != suffix_bits) new_upper--;

    return get_strided_interval(new_stride, new_lower, new_upper);
}
Strided_interval *Strided_interval::Not()
{
    return get_strided_interval(stride, ~upper, ~lower);
}
Strided_interval *Strided_interval::And(Strided_interval *_si)
{
    return Not()->Or(_si->Not())->Not();
}
Strided_interval *Strided_interval::Xor(Strided_interval *_si)
{
    return Not()->Or(_si)->Not()->Or(Or(_si->Not())->Not());
}
Boolean4 *Strided_interval::Compare(Strided_interval *_si)
{
    if(equals(_si))
    {
        return Boolean4::TRUE;
    }
    else
    {
        if (Intersect(_si)->is_bot())
        {
            return Boolean4::FALSE;
        }
        else
        {
            return Boolean4::MAYBE;
        }
    }
}
Boolean4 *Strided_interval::Smaller(Strided_interval *_si)
{
    if (upper < _si->get_lower())
    {
        return Boolean4::TRUE;
    }
    else if (lower > _si->get_upper())
    {
        return Boolean4::FALSE;
    }
    else
    {
        return Boolean4::MAYBE;
    }
}
Strided_interval *Strided_interval::Except(Strided_interval *_other)
{
    std::vector<int> left_hand = si_to_array();
    std::vector<int> right_hand = _other->si_to_array();
    std::vector<int> ret;
    std::set<int> tmp;

    for (int i=0; i<right_hand.size(); i++)
    {
        tmp.insert(right_hand[i]);
    }
    for (int i=0; i<left_hand.size(); i++)
    {
        if (tmp.find(left_hand[i]) == tmp.end())
        {
            ret.push_back(left_hand[i]);
        }
    }
    return Strided_interval::get_strided_interval(ret);

}
Strided_interval *Strided_interval::Widen(Strided_interval *_si)
{
    Strided_interval *ret = this;
    ret = lower <= _si->get_lower() ? ret : ret->remove_lower_bound();
    ret = upper >= _si->get_upper() ? ret : ret->remove_upper_bound();

    return ret;
}
Strided_interval *Strided_interval::Extend()
{
    return this;
}
Strided_interval *Strided_interval::sign_extend()
{
    return this;
}
Boolean4 *Strided_interval::Greater(Strided_interval *_si)
{
    return Smaller(_si)->Not();
}
Boolean4 *Strided_interval::greater_or_equal(Strided_interval *_si)
{
    return Greater(_si)->Or(Compare(_si));
}
Boolean4 *Strided_interval::smaller_or_equal(Strided_interval *_si)
{
    return Smaller(_si)->Or(Compare(_si));
}
int Strided_interval::shared_suffix_mask()
{
    if (is_singleton_set())
    {
        return (int)((1l << width->get_width()) -1);
    }
    int t = number_of_trailing_zeros(stride);
    return (1 << t) - 1;
}
int Strided_interval::shared_prefix_mask()
{
    if (is_singleton_set())
    {
        return (int)((1l << width->get_width()) -1);
    }
    int l = number_of_leading_zeros(lower ^ upper);
    if (l == 0)
    {
        return 0;
    }
    else
    {
        return (1 << width->get_width()-1) >> (l - 1);
    }
}

std::vector<int> Strided_interval::si_to_array()
{
    std::vector<int> ret;
    if (is_singleton_set())
    {
        ret.push_back(lower);
        return ret;
    }
    if (is_bot())
    {
        return ret;
    }

    for (int i=lower; i<=upper; i+=stride)
    {
        ret.push_back(i);
    }
    return ret;
}


/**
* getters and setters
*/
int Strided_interval::get_stride()
{
    return stride;
}
void Strided_interval::set_stride(int _stride)
{
    stride = _stride;
}
int Strided_interval::get_lower()
{
    return lower;
}
void Strided_interval::set_lower(int _lower)
{
    lower = _lower;
}
int Strided_interval::get_upper()
{
    return upper;
}
void Strided_interval::set_upper(int _upper)
{
    upper = _upper;
}
/**
* helpers
*/
std::string Strided_interval::format()
{
    std::stringstream o;
    o << stride << "[" << lower << "," << upper << "]";
    return o.str();
}
void Strided_interval::print(std::ostream &out)
{
    out << this->format();
}

bool Strided_interval::equals(Strided_interval *_si)
{
    return (stride == _si->get_stride()) && (lower == _si->get_lower()) && (upper == _si->get_upper());
}
bool Strided_interval::is_singleton_set()
{
    return stride == 0;
}
bool Strided_interval::is_top()
{
    return (stride == 1) && (lower == -(1 << (width->get_width()-1))) && (upper == ((1 << (width->get_width() - 1)) - 1));
}
bool Strided_interval::is_bot()
{
    return (stride == -1) && (lower == 0) && (upper == 0);
}
bool Strided_interval::is_zero()
{
    return is_singleton_set() && lower == 0;
}
bool Strided_interval::is_one()
{
    return is_singleton_set() && lower == 1;
}
bool Strided_interval::is_interval()
{
    return stride == 1;
}
bool Strided_interval::contains(int _num)
{
    return !(lower > _num || upper < _num) && (is_singleton_set() && lower == _num) || ((_num - lower) % stride == 0);
}
bool Strided_interval::contains(Strided_interval *_si)
{
    if (is_bot())
    {
        return false;
    }
    else if (_si->is_bot())
    {
        return true;
    }
    else if (is_singleton_set())
    {
        return equals(_si);
    }
    else if (_si->is_singleton_set())
    {
        return contains(_si->get_lower());
    }
    else
    {
        return (_si->get_stride() % stride == 0) && (_si->get_lower() >= lower) && (_si->get_lower() <= upper)
                                                 && (_si->get_upper() >= lower) && (_si->get_upper() <= upper)
                                                 && (contains(_si->get_lower()));
    }
}
bool Strided_interval::is_lower_bound_minimal()
{
    return lower == width->get_minimum_value();
}
bool Strided_interval::is_upper_bound_maximal()
{
    return upper == width->get_maximum_value();
}

/**
* private attributes and methods
*/
Strided_interval::Strided_interval(int _stride, int _lower, int _upper)
{
    stride = _stride;
    lower = _lower;
    upper = _upper;
}


/**
* helper functions which are only used in this file
*/
//unsigned int_to_unsigned(int x)
//{
//    return x > 0 ? x : ((1 << 32) + x);
//}
//int unsigned_to_int(unsigned x)
//{
//    return 0;
//}
int number_of_trailing_zeros(int i)
{
    int y;
    if (i == 0)return 32;
    int n = 31;
    y = i << 16; if (y != 0){n -= 16; i = y;}
    y = i << 8; if (y != 0) { n = n - 8; i = y; }
    y = i << 4; if (y != 0) { n = n - 4; i = y; }
    y = i << 2; if (y != 0) { n = n - 2; i = y; }

    return n-((unsigned)(i << 1) >> 31);
}
int number_of_leading_zeros(int i)
{
    unsigned tmp = (unsigned) i;
    if (tmp == 0)
        return 32;
    int n = 1;
    if (tmp >> 16 == 0) { n += 16; tmp <<= 16; }
    if (tmp >> 24 == 0) { n +=  8; tmp <<=  8; }
    if (tmp >> 28 == 0) { n +=  4; tmp <<=  4; }
    if (tmp >> 30 == 0) { n +=  2; tmp <<=  2; }
    n -= tmp >> 31;
    return n;
}

