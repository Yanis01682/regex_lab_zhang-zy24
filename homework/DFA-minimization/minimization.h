#ifndef REGEX_LAB_MINIMIZATION_H
#define REGEX_LAB_MINIMIZATION_H

#include "DFA.h"

template<typename T>
DFA<T> minimization(const DFA<T> &old_dfa) {
    // TODO: ~90 lines
    return DFA<T>(0);
}

template DFA<char> minimization(const DFA<char> &old_dfa);

#endif //REGEX_LAB_MINIMIZATION_H
