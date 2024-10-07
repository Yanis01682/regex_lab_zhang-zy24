#include <iostream>
#include "expression-parser/to_polish.h"
#include "expression-parser/parser.h"
#include "ParseTree-to-eNFA/converter.h"
#include "subset-construction/subset_construction.h"
#include "DFA-minimization/minimization.h"
#include "DFA-accept/accept.h"

int main() {
    std::string expression;
    std::cout << std::boolalpha;
    std::cin >> expression;
    std::vector<COE> regex;
    for (auto &&j: expression) {
        if (j != '@')
            regex.emplace_back(j);
        else
            regex.push_back(epsilon<COE>);
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
        std::vector<COE> s;
        for (auto &&j: str) {
            if (j != '-')
                s.emplace_back(j);
        }
        bool oos = false;
        for (auto &&c: s) {
            if (!automata.Sigma.count(c)) {
                std::cout << "Out of Sigma!" << std::endl;
                oos = true;
                break;
            }
        }
        if (!oos)
            std::cout << DFA_accept(automata, s) << std::endl;
    }

    return 0;
}
