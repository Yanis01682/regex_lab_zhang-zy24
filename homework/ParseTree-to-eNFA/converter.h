#ifndef REGEX_LAB_CONVERTER_H
#define REGEX_LAB_CONVERTER_H

#include "NFA.h"
#include "consts.h"
#include "parse_tree.h"
#include <algorithm>
#include <cstdlib>
#include <string>
#include <memory>
#include <functional>

template <typename T>
NFA<T> PT_to_eNFA(const ParseTree<T>& pt) {
    using State = typename NFA<T>::state;
    using NFA_Type = NFA<T>;
    using Node = typename ParseTree<T>::node;

    std::function<NFA_Type(std::shared_ptr<Node>)> build = 
        [&](std::shared_ptr<Node> node) -> NFA_Type {
        
        NFA_Type nfa;
        if (!node || node->children.empty()) return nfa;

        auto head_node = node->children[0];
        T val = head_node->label_value;

        //1. 并运算 (+)
        if (val == regex_union<T>) {
            auto n1 = build(node->children[1]); 
            auto n2 = build(node->children[2]); 

            auto start = std::make_shared<State>();
            auto final = std::make_shared<State>();

            start->epsilon_transition.insert(n1.q0);
            start->epsilon_transition.insert(n2.q0);
            for (auto f : n1.F) f->epsilon_transition.insert(final);
            for (auto f : n2.F) f->epsilon_transition.insert(final);

            nfa.Q = n1.Q; nfa.Q.insert(n2.Q.begin(), n2.Q.end());
            nfa.Q.insert(start); nfa.Q.insert(final);
            nfa.Sigma = n1.Sigma; nfa.Sigma.insert(n2.Sigma.begin(), n2.Sigma.end());
            nfa.q0 = start;
            nfa.F = {final};
        }
        //2. 连接运算
        else if (val == regex_concatenation<T>) {
            auto n1 = build(node->children[1]);
            auto n2 = build(node->children[2]);

            for (auto f : n1.F) f->epsilon_transition.insert(n2.q0);

            nfa.Q = n1.Q; nfa.Q.insert(n2.Q.begin(), n2.Q.end());
            nfa.Sigma = n1.Sigma; nfa.Sigma.insert(n2.Sigma.begin(), n2.Sigma.end());
            nfa.q0 = n1.q0; 
            nfa.F = n2.F;   
        }
        //3. 闭包运算
        else if (val == regex_closure<T>) {
            auto n1 = build(node->children[1]);

            auto start = std::make_shared<State>();
            auto final = std::make_shared<State>();

            start->epsilon_transition.insert(n1.q0);
            start->epsilon_transition.insert(final); 
            for (auto f : n1.F) {
                f->epsilon_transition.insert(n1.q0); 
                f->epsilon_transition.insert(final); 
            }

            nfa.Q = n1.Q; nfa.Q.insert(start); nfa.Q.insert(final);
            nfa.Sigma = n1.Sigma;
            nfa.q0 = start;
            nfa.F = {final};
        }
        //4. 基础符号或 Epsilon
        else {
            auto start = std::make_shared<State>();
            auto final = std::make_shared<State>();

            if (val == epsilon<T>) {
                start->epsilon_transition.insert(final);
            } else {
                start->transition[val].insert(final);
                nfa.Sigma.insert(val);
            }

            nfa.Q = {start, final};
            nfa.q0 = start;
            nfa.F = {final};
        }

        return nfa;
    };

    if (pt.root) {
        return build(pt.root);
    }
    // 处理空树的情况，返回一个带死状态的 NFA，防止 subset_construction 崩溃
    NFA_Type empty_nfa;
    return empty_nfa; // 因为 subset_construction 已经加了判空保护，这里返回默认空 NFA 即可
}

template NFA<char> PT_to_eNFA<char>(const ParseTree<char>& pt);

#endif // REGEX_LAB_CONVERTER_H