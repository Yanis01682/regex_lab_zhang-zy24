#ifndef REGEX_LAB_ACCEPT_H
#define REGEX_LAB_ACCEPT_H

#include <vector>
#include <string>
#include "DFA.h"

template<typename T>
bool DFA_accept(const DFA<T> &dfa, const std::vector<T> s) {
    // TODO
    return false;
}

template<typename T>
bool DFA_accept(const DFA<T> &dfa, const std::basic_string<T> &s) {
    std::vector<T> v(s.begin(), s.end());
    return DFA_accept(dfa, v);
}

#endif //REGEX_LAB_ACCEPT_H
