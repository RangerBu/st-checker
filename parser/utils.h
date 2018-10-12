//
// Created by Samson on 2018/5/30.
//

#ifndef VERIFY_ST_PROGRAMS_UTILS_H
#define VERIFY_ST_PROGRAMS_UTILS_H

#include <iostream>
#include <string>

class utils
{
public:
    // 去掉两端的空格
    static std::string &trim(std::string &_str);

    // 判断一个字符串是否是数字
    static bool is_number(std::string _str);

    // 将字符串转换为对应的数字
    static int to_number(std::string _str);

    static char *append(char *_ch1, char *_ch2);

};


#endif //VERIFY_ST_PROGRAMS_UTILS_H
