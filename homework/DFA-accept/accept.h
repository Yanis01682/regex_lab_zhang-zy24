#ifndef REGEX_LAB_ACCEPT_H
#define REGEX_LAB_ACCEPT_H

#include "DFA.h"
#include <string>
#include <vector>

template <typename T>
bool DFA_accept(const DFA<T>& dfa, const std::vector<T> s) {
    for (auto&& c : s) {
        if (!dfa.Sigma.count(c)) {
            return false;
        }
    }
    // DONE: ~5 lines
    // 获取起始状态
    auto current = dfa.q0;
    if (current == nullptr) return false;

    // 3. 模拟 DFA 运行
    for (auto&& c : s) {
        // 查找转移边
        auto it = current->transition.find(c);
        if (it != current->transition.end()) {
            current = it->second;
        } else {
            // 如果 DFA 是完全的，理论上不该进这里；
            // 但如果是非完全 DFA，走到死路直接拒绝
            return false;
        }
        
        // 双重保险：防止空指针
        if (current == nullptr) return false;
    }

    // 4. 检查是否停留在终态
    if (dfa.F.find(current) != dfa.F.end()) {
        return true;
    }
    return false;
}

template <typename T>
bool DFA_accept(const DFA<T>& dfa, const std::basic_string<T>& s) {
    std::vector<T> v(s.begin(), s.end());
    return DFA_accept(dfa, v);
}

#endif // REGEX_LAB_ACCEPT_H
