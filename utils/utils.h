#ifndef UTILS_H
#define UTILS_H

#include <string>

class utils
{
    public:
         static std::string &trim(std::string &);
         static int gcd(int, int);
         static int extend_euclidean(int, int, int &, int &);

    public:
        utils();
        virtual ~utils();

    protected:
    private:
};

#endif // UTILS_H
