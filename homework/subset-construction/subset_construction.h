//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_SUBSET_CONSTRUCTION_H
#define REGEX_LAB_SUBSET_CONSTRUCTION_H

#include <functional>
#include "NFA.h"
#include "DFA.h"

template<typename T>
DFA<T> subset_construction(const NFA<T> &n) {
    // TODO
    return DFA<T>(0);
}

const std::function<DFA<char>(const NFA<char> &)> subset_construction_char = subset_construction<char>;

#endif //REGEX_LAB_SUBSET_CONSTRUCTION_H
