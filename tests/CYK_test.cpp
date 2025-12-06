#include "CYK-algorithm/CYK.h"
#include <fstream>
#include <iostream>

CFG<char> g = {
    {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'S'},
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {},
    'S',
};

std::vector<char> gen;

bool gen_str(const std::shared_ptr<ParseTree<char>::node>& n) {
    constexpr auto Variable = ParseTree<char>::node::LabelType::Variable;
    constexpr auto Terminal = ParseTree<char>::node::LabelType::Terminal;
    if (n->label_type == Variable) {
        bool success = true;
        std::vector<char> p;
        for (auto&& c : n->children) {
            success = success && gen_str(c);
            p.push_back(c->label_value);
        }
        return success && g.P[n->label_value].count(p);
    }
    if (n->label_type == Terminal) {
        gen.push_back(n->label_value);
        return true;
    }
    return false;
}


int main() {
    for (auto&& v : g.V) {
        g.P[v] = {};
    }
    g.P['S'] = {{'0'}};
    if (CYK_algorithm<char>(g, {'0'}).root == nullptr) {
        std::cout << "CYK algorithm assignment has not been completed." << std::endl;
        return 0;
    }
    std::ifstream fin("../testcases/input_CYK.txt");
    // auto &fin = std::cin;
    for (int t = 0; t < 100; ++t) {
        for (auto&& v : g.V) {
            g.P[v] = {};
        }
        while (true) {
            std::string line;
            fin >> line;
            if (line[0] == '=') {
                break;
            }
            g.P[line[0]].insert(std::vector{line[3], line[4]});
        }
        while (true) {
            std::string line;
            fin >> line;
            if (line[0] == '=') {
                break;
            }
            g.P[line[0]].insert(std::vector{line[3]});
        }
        while (true) {
            std::string line;
            fin >> line;
            if (line[0] == '=') {
                break;
            }
            gen.clear();
            std::vector<char> str;
            for (auto&& c : line) {
                str.push_back(c);
            }
            const auto pt = CYK_algorithm<char>(g, str);
            if (!gen_str(pt.root) || gen != str) {
                std::cout << "Wrong: " << line << std::endl;
                return 1;
            }
        }
        std::cout << "CYK Test " << t << " finished." << std::endl;
    }
    return 0;
}
