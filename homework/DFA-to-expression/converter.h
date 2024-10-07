//
// Created by 张英奇 on 24-10-6.
//

#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include <vector>
#include <functional>
#include "DFA.h"

template<typename T>
std::vector<T> DFA_to_exp(const DFA<T> &dfa) {
    // TODO
    return std::vector<T>();
}

const std::function<std::vector<char>(const DFA<char> & )> DFA_to_exp_char = DFA_to_exp<char>;

#endif //REGEX_LAB_CONVERTER_H
