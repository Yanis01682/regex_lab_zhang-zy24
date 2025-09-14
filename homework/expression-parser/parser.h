#ifndef REGEX_LAB_PARSER_H
#define REGEX_LAB_PARSER_H

#include "consts.h"
#include "parse_tree.h"
#include <vector>

template <typename T>
ParseTree<T> polish_parser(const std::vector<T>& regex) {
    // TODO: ~30 lines
    return ParseTree<T>();
}

template ParseTree<char> polish_parser<char>(const std::vector<char>& regex);

#endif // REGEX_LAB_PARSER_H
