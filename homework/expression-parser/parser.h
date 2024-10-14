#ifndef REGEX_LAB_PARSER_H
#define REGEX_LAB_PARSER_H

#include <vector>
#include "parse_tree.h"
#include "consts.h"

template<typename T>
ParseTree<T> polish_parser(const std::vector<T> &regex) {
    // TODO: ~50 lines
    return ParseTree<T>(0);
}

template ParseTree<char> polish_parser<char>(const std::vector<char> &regex);

#endif //REGEX_LAB_PARSER_H
