#ifndef REGEX_LAB_SUBSET_CONSTRUCTION_H
#define REGEX_LAB_SUBSET_CONSTRUCTION_H

#include "DFA.h"
#include "NFA.h"
#include <algorithm>

template <typename T>
DFA<T> subset_construction(const NFA<T>& n) {
    // TODO: ~70 lines
    return DFA<T>();
}

template DFA<char> subset_construction<char>(const NFA<char>& n);

#endif // REGEX_LAB_SUBSET_CONSTRUCTION_H
