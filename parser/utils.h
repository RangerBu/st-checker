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
    // ȥ�����˵Ŀո�
    static std::string &trim(std::string &_str);

    // �ж�һ���ַ����Ƿ�������
    static bool is_number(std::string _str);

    // ���ַ���ת��Ϊ��Ӧ������
    static int to_number(std::string _str);

    static char *append(char *_ch1, char *_ch2);

};


#endif //VERIFY_ST_PROGRAMS_UTILS_H
