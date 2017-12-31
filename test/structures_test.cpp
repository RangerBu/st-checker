//#define STRUCTURES_TEST

#ifdef STRUCTURES_TEST

#include <iostream>
#include <set>

#include "../analyzer/structures/Boolean4.h"
#include "../analyzer/structures/Bits_vector_1.h"
#include "../analyzer/structures/Bits_vector_8.h"
#include "../analyzer/structures/Strided_interval.h"

using namespace std;
int main()
{
    /**
    * strided-intervals test cases
    */
    Strided_interval *top = Strided_interval::get_top();
    Strided_interval *bot = Strided_interval::get_bot();

    cout << top->format() << endl;

    cout << bot->format() << endl;

    Strided_interval *si0 = Strided_interval::get_strided_interval(1, -2147483648, 2147483647);
    Strided_interval *si1 = Strided_interval::get_interval(-2147483648, 2147483647);
    Strided_interval *si2 = Strided_interval::get_singleton_set(20);

    cout << si0->format() << endl;
    cout << si1->format() << endl;
    cout << si2->format() << endl << endl;

    cout << si0->equals(si1) << endl;
    cout << si0->equals(top) << endl << endl;

    cout << si2->is_singleton_set() << endl;
    cout << si1->is_interval() << endl << endl;

    cout << si1->is_lower_bound_minimal() << endl;
    cout << si1->is_upper_bound_maximal() << endl << endl;

    cout << si1->contains(20) << endl;
    cout << si1->contains(si2) << endl << endl;

    Strided_interval *si3 = Strided_interval::get_strided_interval(1, 0, 54);
    Strided_interval *si4 = Strided_interval::get_singleton_set(50);
    Strided_interval *si5 = Strided_interval::get_singleton_set(60);
    Strided_interval *si6 = Strided_interval::get_singleton_set(18);
    Strided_interval *si7 = Strided_interval::get_strided_interval(3, 51, 60);

    cout << si3->Add(si4)->format() << endl;
    cout << si3->Add(50)->format() << endl << endl;

    cout << si3->Sub(50)->format() << endl;
    cout << si3->Sub(si4)->format() << endl << endl;

    cout << si3->Union(si4)->format() << endl;
    cout << si4->Union(si3)->format() << endl;
    cout << si3->Union(top)->format() << endl;
    cout << si3->Union(bot)->format() << endl << endl;

    cout << si4->format() << " " << si5->format() << endl;
    cout << si4->Union(si5)->Union(si6)->format()<< endl << endl;

    cout << si3->Intersect(si4)->format() << endl;

    cout << si3->Negate()->format() << endl << endl;;

    cout << si3->Xor(si7)->format() << endl;
    std::set<int> or_set;
    for (int i=0; i<55; i++)
    {
        for (int j=51; j<61; j+=3)
        {
            or_set.insert((i^j));
        }
    }
    std::set<int>::iterator it = or_set.begin();
    for (; it!=or_set.end(); it++)
    {
        cout << *it << endl;
    }
    cout << endl;


    cout << si4->Widen(si5)->format() << endl;
    cout << si5->Widen(si4)->format() << endl << endl;


    Boolean4 *t = Boolean4::TRUE;
    Boolean4 *f = Boolean4::FALSE;
    Boolean4 *bbot = Boolean4::BOT;
    Boolean4 *btop = Boolean4::MAYBE;

    cout << f->Join(btop)->format() << endl;


    cout << endl;

    cout << si3->Add(Strided_interval::get_bot())->format() << endl;

    Strided_interval *si8 = Strided_interval::get_singleton_set(50)->remove_lower_bound();

    cout << si8->Intersect(Strided_interval::get_top())->format() << endl << endl;

    std::vector<int> arr;
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(7);
    Strided_interval *si9 = Strided_interval::get_strided_interval(arr);

    std::cout << si9->format() << std::endl << endl;

    Strided_interval *si10 = Strided_interval::get_strided_interval(2, 4, 8);
    Strided_interval *si11 = Strided_interval::get_strided_interval(3, 30, 90);
    std::cout << si10->Except(si11)->format() << std::endl;


}

#endif // STRUCTURES_TEST
