#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include "NFA.h"
#include "consts.h"
#include "parse_tree.h"
#include <algorithm>
#include <cstdlib>
#include <string>

template <typename T>
NFA<T> PT_to_eNFA(const ParseTree<T>& pt) {
    // TODO: ~80 lines
    return NFA<T>();
}

template NFA<char> PT_to_eNFA<char>(const ParseTree<char>& pt);

#endif // REGEX_LAB_CONVERTER_H
