#include "DFA-accept/accept.h"
#include "expression-parser/to_polish.h"
#include "lib_char.h"
#include <fstream>
#include <iostream>
#include <regex>

int main() {
    std::ifstream fin("../testcases/input.txt");
    for (int t = 0; t < 100; ++t) {
        std::string expression;
        fin >> expression;
        std::vector<char> regex;
        std::string std_expression;
        for (auto&& j : expression) {
            if (j != '+') {
                std_expression.push_back(j);
            } else {
                std_expression.push_back('|');
            }
            regex.emplace_back(j);
        }
        std::regex std_regex(std_expression, std::regex::optimize);
        const auto automata = minimization(subset_construction(PT_to_eNFA(polish_parser(to_polish(regex)))));
        for (int i = 0; i < 100; ++i) {
            std::string str;
            fin >> str;
            std::vector<char> s;
            for (auto&& j : str) {
                s.emplace_back(j);
            }
            std::cmatch m;
            if (std::regex_match(str.c_str(), m, std_regex) != DFA_accept(automata, s)) {
                std::cout << "Wrong: " << str << " with " << expression << std::endl;
                return 1;
            }
        }
        std::cout << "Regex Test " << t << " finished." << std::endl;
    }
    return 0;
}
