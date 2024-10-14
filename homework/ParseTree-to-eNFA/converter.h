#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include <cstdlib>
#include <algorithm>
#include <string>
#include "parse_tree.h"
#include "NFA.h"
#include "consts.h"
#include "merge_NFA.h"

template<typename T>
NFA<T> PT_to_eNFA(const ParseTree<T> &pt) {
    // TODO: ~70 lines
    return NFA<T>(0);
}

template NFA<char> PT_to_eNFA<char>(const ParseTree<char> &pt);

#endif //REGEX_LAB_CONVERTER_H
