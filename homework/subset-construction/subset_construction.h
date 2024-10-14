#ifndef REGEX_LAB_SUBSET_CONSTRUCTION_H
#define REGEX_LAB_SUBSET_CONSTRUCTION_H

#include <algorithm>
#include "NFA.h"
#include "DFA.h"

template<typename T>
DFA<T> subset_construction(const NFA<T> &n) {
    // TODO: ~100 lines
    return DFA<T>(0);
}

template DFA<char> subset_construction<char>(const NFA<char> &n);

#endif //REGEX_LAB_SUBSET_CONSTRUCTION_H
