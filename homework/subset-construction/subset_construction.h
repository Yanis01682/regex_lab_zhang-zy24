#ifndef REGEX_LAB_SUBSET_CONSTRUCTION_H
#define REGEX_LAB_SUBSET_CONSTRUCTION_H

#include "DFA.h"
#include "NFA.h"
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <memory>

template <typename T>
DFA<T> subset_construction(const NFA<T>& n) {
    using NFAStatePtr = std::shared_ptr<typename NFA<T>::state>;
    using DFAStatePtr = std::shared_ptr<typename DFA<T>::state>;
    using StateSet = std::set<NFAStatePtr>;

    DFA<T> dfa;
    dfa.Sigma = n.Sigma;

    // 1. 处理空 NFA
    if (n.q0 == nullptr) {
        auto dead_state = std::make_shared<typename DFA<T>::state>();
        dead_state->name = "dead";
        for (const auto& c : dfa.Sigma) {
            dead_state->transition[c] = dead_state;
        }
        dfa.q0 = dead_state;
        dfa.Q.insert(dead_state);
        return dfa;
    }

    // 2. 辅助函数
    auto get_epsilon_closure = [&](const StateSet& states) -> StateSet {
        StateSet closure = states;
        std::queue<NFAStatePtr> work_queue;
        for (const auto& s : states) if (s) work_queue.push(s);

        while (!work_queue.empty()) {
            auto u = work_queue.front();
            work_queue.pop();
            if (!u) continue;
            for (const auto& v : u->epsilon_transition) {
                if (v && closure.find(v) == closure.end()) {
                    closure.insert(v);
                    work_queue.push(v);
                }
            }
        }
        return closure;
    };

    auto is_accepting = [&](const StateSet& states) -> bool {
        for (const auto& s : states) {
            if (n.F.count(s)) return true;
        }
        return false;
    };

    // 3. 构造起始状态
    StateSet start_set = {n.q0};
    StateSet start_closure = get_epsilon_closure(start_set);

    auto dfa_start = std::make_shared<typename DFA<T>::state>();
    dfa_start->name = "start";
    dfa.q0 = dfa_start;
    dfa.Q.insert(dfa_start);
    if (is_accepting(start_closure)) dfa.F.insert(dfa_start);

    // 4. BFS 主循环
    std::map<StateSet, DFAStatePtr> mapping;
    std::queue<StateSet> worklist;

    mapping[start_closure] = dfa_start;
    worklist.push(start_closure);

    while (!worklist.empty()) {
        StateSet current_set = worklist.front();
        worklist.pop();
        DFAStatePtr current_dfa_node = mapping[current_set];

        // 遍历字母表，确保 DFA 是完全的 (Total DFA)
        for (const auto& symbol : dfa.Sigma) {
            StateSet next_set_raw;
            
            // move(S, a)
            for (const auto& node : current_set) {
                if (node && node->transition.count(symbol)) {
                    for (const auto& target : node->transition.at(symbol)) {
                        if (target) next_set_raw.insert(target);
                    }
                }
            }

            // ECLOSE(move(S, a))
            // 注意：即使 next_set_raw 为空，也要算 closure (结果为空)，并映射到死状态
            StateSet next_closure = get_epsilon_closure(next_set_raw);

            if (mapping.find(next_closure) == mapping.end()) {
                auto new_node = std::make_shared<typename DFA<T>::state>();
                if (next_closure.empty()) new_node->name = "trap"; // 调试用
                
                mapping[next_closure] = new_node;
                dfa.Q.insert(new_node);
                if (is_accepting(next_closure)) dfa.F.insert(new_node);
                worklist.push(next_closure);
            }

            current_dfa_node->transition[symbol] = mapping[next_closure];
        }
    }

    return dfa;
}

template DFA<char> subset_construction<char>(const NFA<char>& n);

#endif // REGEX_LAB_SUBSET_CONSTRUCTION_H