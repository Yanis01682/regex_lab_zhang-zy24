#ifndef REGEX_LAB_MINIMIZATION_H
#define REGEX_LAB_MINIMIZATION_H

#include "DFA.h"
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <memory>

template <typename T>
DFA<T> minimization(const DFA<T>& dfa) {
    // DONE: ~90 lines
    using StatePtr = std::shared_ptr<typename DFA<T>::state>;
    std::vector<StatePtr> states(dfa.Q.begin(), dfa.Q.end());
    int n = states.size();
    
    // 建立 状态指针 -> 索引 的映射，方便快速查找
    std::map<StatePtr, int> state_to_id;
    for (int i = 0; i < n; ++i) {
        state_to_id[states[i]] = i;
    }

    // 2. 初始化填表 (distinguishable table)
    // table[i][j] = true 表示状态 i 和状态 j 是“可区分的”
    // 我们只需要用到上三角或下三角，这里直接开二维数组简单处理
    std::vector<std::vector<bool>> distinct(n, std::vector<bool>(n, false));

    // 初始标记：终态和非终态是可区分的
    // dfa.F 包含了所有的终态
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            bool i_is_final = dfa.F.count(states[i]);
            bool j_is_final = dfa.F.count(states[j]);
            if (i_is_final != j_is_final) {
                distinct[i][j] = distinct[j][i] = true;
            }
        }
    }

    // 3. 迭代填表 (核心算法)
    bool changed = true;
    while (changed) {
        changed = false;
        // 遍历所有尚未被标记为可区分的状态对 (i, j)
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (!distinct[i][j]) {
                    // 尝试通过所有字符，看能否把它们区分开
                    for (const auto& symbol : dfa.Sigma) {
                        // 获取转移后的目标状态
                        // 注意：这里假设 DFA 是完全的 (我们在实验2里保证了这点)
                        // 如果不完全，需要处理 nullptr，视为死状态
                        auto target_i = states[i]->transition.count(symbol) ? states[i]->transition.at(symbol) : nullptr;
                        auto target_j = states[j]->transition.count(symbol) ? states[j]->transition.at(symbol) : nullptr;

                        // 如果跳转到的两个状态已经是可区分的，那 i 和 j 也是可区分的
                        // (注意处理 nullptr：如果一个跳到死状态一个没跳，或者都跳死状态，逻辑要一致)
                        // 简单起见，如果我们在实验2做了完全DFA，这里 target 不会是 nullptr
                        
                        if (target_i && target_j) {
                            int u = state_to_id[target_i];
                            int v = state_to_id[target_j];
                            if (distinct[u][v]) {
                                distinct[i][j] = distinct[j][i] = true;
                                changed = true;
                                break; // 只要有一个字符能区分，就足够了
                            }
                        } 
                        else if (target_i != target_j) {
                            // 一个有边一个没边 (不完全DFA的情况)，也是可区分的
                            distinct[i][j] = distinct[j][i] = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    // 4. 合并等价状态 (构建新 DFA)
    DFA<T> min_dfa;
    min_dfa.Sigma = dfa.Sigma;

    // group[i] 表示第 i 个状态属于哪个新状态编号
    std::vector<int> group(n, -1);
    std::vector<StatePtr> new_states; // 存储新创建的状态对象

    for (int i = 0; i < n; ++i) {
        if (group[i] == -1) {
            // 发现一个新的等价类，创建一个新状态
            auto new_state = std::make_shared<typename DFA<T>::state>();
            // 随便起个名字，或者把合并的状态名拼起来
            new_state->name = states[i]->name; 
            
            int current_group_id = new_states.size();
            group[i] = current_group_id;
            new_states.push_back(new_state);
            min_dfa.Q.insert(new_state);

            // 标记所有和 i 不可区分的状态为同一组
            for (int j = i + 1; j < n; ++j) {
                if (!distinct[i][j]) {
                    group[j] = current_group_id;
                }
            }
        }
    }

    // 5. 设置新状态的属性 (起始态、终态、转移)
    for (int i = 0; i < n; ++i) {
        int g_id = group[i];
        auto new_s = new_states[g_id];

        // 如果旧状态是起始态，新状态就是起始态
        if (states[i] == dfa.q0) {
            min_dfa.q0 = new_s;
        }

        // 如果旧状态是终态，新状态就是终态 (等价类中的状态同为终态或同为非终态)
        if (dfa.F.count(states[i])) {
            min_dfa.F.insert(new_s);
        }

        // 设置转移：只需要设置一次即可 (因为等价类中转移一致)
        // 我们利用 new_s->transition 是否为空来判断是否已经设置过
        // 但为了保险，我们可以每次都设置一遍(覆盖)，或者加个标记
        // 这里简单处理：直接遍历字母表设置
        for (const auto& symbol : dfa.Sigma) {
            if (states[i]->transition.count(symbol)) {
                auto target_old = states[i]->transition.at(symbol);
                if (target_old) {
                    int target_old_id = state_to_id[target_old];
                    int target_new_group = group[target_old_id];
                    new_s->transition[symbol] = new_states[target_new_group];
                }
            }
        }
    }

    return min_dfa;
}

template DFA<char> minimization(const DFA<char>& old_dfa);

#endif // REGEX_LAB_MINIMIZATION_H
