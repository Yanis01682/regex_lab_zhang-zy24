#include <iostream>
#include "DFA-accept/accept.h"
#include "expression-parser/to_polish.h"
#include "lib_char.h"

int main() {
    std::string expression;
    std::cout << std::boolalpha;
    std::cin >> expression;
    std::vector<char> regex;
    for (auto &&j: expression) {
        if (j != '@')
            regex.emplace_back(j);
        else
            regex.push_back(epsilon<char>);
    }
    auto automata =
            minimization(
                    subset_construction(
                            PT_to_eNFA(
                                    polish_parser(
                                            to_polish(
                                                    regex
                                            )
                                    )
                            )
                    )
            );
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        std::vector<char> s;
        for (auto &&j: str) {
            if (j != '-')
                s.emplace_back(j);
        }
        std::cout << DFA_accept(automata, s) << std::endl;
    }
    return 0;
}
