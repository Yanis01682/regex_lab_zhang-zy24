//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include <cstdlib>
#include <algorithm>
#include <string>
#include <functional>
#include "parse_tree.h"
#include "NFA.h"
#include "consts.h"
#include "merge_NFA.h"

template<typename T>
NFA<T> PT_to_eNFA(const ParseTree<T> &pt) {
    // TODO
    return NFA<T>(0);
}

const std::function<NFA<char>(const ParseTree<char> &)> PT_to_eNFA_char = PT_to_eNFA<char>;

#endif //REGEX_LAB_CONVERTER_H
