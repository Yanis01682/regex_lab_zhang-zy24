#ifndef REGEX_LAB_LIB_CHAR_H
#define REGEX_LAB_LIB_CHAR_H

#include <functional>
#include <vector>
#include "parse_tree.h"
#include "NFA.h"
#include "DFA.h"
#include "consts.h"

template<typename T>
ParseTree<T> polish_parser(const std::vector<T> &regex);

extern template ParseTree<char> polish_parser<char>(const std::vector<char> &regex);

template<typename T>
NFA<T> PT_to_eNFA(const ParseTree<T> &pt);

extern template NFA<char> PT_to_eNFA<char>(const ParseTree<char> &pt);

template<typename T>
DFA<T> subset_construction(const NFA<T> &n);

extern template DFA<char> subset_construction<char>(const NFA<char> &n);

template<typename T>
DFA<T> minimization(const DFA<T> &old_dfa);

extern template DFA<char> minimization<char>(const DFA<char> &old_dfa);

#endif //REGEX_LAB_LIB_CHAR_H
