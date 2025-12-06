#ifndef REGEX_LXB_CFG_H
#define REGEX_LXB_CFG_H

#include <map>
#include <set>
#include <vector>

template <typename X>
class CFG {
public:
    // 变元的集合
    std::set<X> V;

    // 终结符号的集合
    std::set<X> T;

    // 产生式的集合（X -> a_1 | a_2 | ... | a_n ）
    std::map<X, std::set<std::vector<X>>> P;

    // 初始符号
    X S;
};

#endif // REGEX_LXB_CFG_H
