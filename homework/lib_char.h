#ifndef REGEX_LAB_LIB_CHAR_H
#define REGEX_LAB_LIB_CHAR_H

#include "DFA.h"
#include "NFA.h"
#include "consts.h"
#include "parse_tree.h"
#include <vector>

template <typename T>
ParseTree<T> polish_parser(const std::vector<T>& regex);

extern template ParseTree<char> polish_parser<char>(const std::vector<char>& regex);

template <typename T>
NFA<T> PT_to_eNFA(const ParseTree<T>& pt);

extern template NFA<char> PT_to_eNFA<char>(const ParseTree<char>& pt);

template <typename T>
DFA<T> subset_construction(const NFA<T>& n);

extern template DFA<char> subset_construction<char>(const NFA<char>& n);

template <typename T>
DFA<T> minimization(const DFA<T>& old_dfa);

extern template DFA<char> minimization<char>(const DFA<char>& old_dfa);

#include "expression-parser/parser.h"
#include "ParseTree-to-eNFA/converter.h"
#include "subset-construction/subset_construction.h"
#include "DFA-minimization/minimization.h"

#endif // REGEX_LAB_LIB_CHAR_H
