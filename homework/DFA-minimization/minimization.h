//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_MINIMIZATION_H
#define REGEX_LAB_MINIMIZATION_H

#include <functional>
#include "DFA.h"

template<typename T>
DFA<T> minimization(const DFA<T> &old_dfa) {
    // TODO
    return DFA<T>(0);
}

const std::function<DFA<char>(const DFA<char> &)> minimization_char = minimization<char>;

#endif //REGEX_LAB_MINIMIZATION_H
