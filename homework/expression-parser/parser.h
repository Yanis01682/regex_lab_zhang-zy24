//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_PARSER_H
#define REGEX_LAB_PARSER_H

#include <vector>
#include <functional>
#include "parse_tree.h"
#include "consts.h"

template<typename T>
ParseTree<T> polish_parser(const std::vector<T> &regex) {
    // TODO
    return ParseTree<T>(0);
}

const std::function<ParseTree<char>(const std::vector<char> &)> polish_parser_char = polish_parser<char>;

#endif //REGEX_LAB_PARSER_H
