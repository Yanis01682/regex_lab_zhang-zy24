#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include <vector>
#include "DFA.h"

template<typename T>
std::vector<T> DFA_to_exp(const DFA<T> &dfa) {
    // TODO: TODO
    return std::vector<T>();
}

template std::vector<char> DFA_to_exp<char>(const DFA<char> &dfa);

#endif //REGEX_LAB_CONVERTER_H
