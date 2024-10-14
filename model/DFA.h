#ifndef REGEX_LAB_DFA_H
#define REGEX_LAB_DFA_H

#include <set>
#include <map>
#include <string>

template<typename T>
class DFA {
public:

    // DFA 的状态类型定义
    struct state {
        // 状态名，以便于调试
        std::string name;
        // 状态转移映射
        std::map<T, state *> transition;
    };

    // 状态集
    std::set<state *> Q;

    // 输入符号集
    std::set<T> Sigma;

    // 转移函数
    static state *delta(state *q, T a) {
        auto it = q->transition.find(a);
        return it->second;
    };

    // 开始状态
    state *q0;

    // 终态集合
    std::set<state *> F;

    // 构造一个状态数量不能超过 buf_size 的 DFA
    explicit DFA(std::size_t buf_size) {
        buf = new state[buf_size];
    }

    // 存放 state 的内存空间
    state *buf;

    // 回收内存空间
    ~DFA() {
        delete[] buf;
    }

    // 禁止拷贝
    DFA(const DFA &) = delete;

    // 禁止拷贝
    DFA &operator=(const DFA &) = delete;

    // 可以移动
    DFA(DFA &&m) noexcept {
        Q = std::move(m.Q);
        Sigma = std::move(m.Sigma);
        q0 = std::move(m.q0);
        F = std::move(m.F);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }

    // 可以移动
    DFA &operator=(DFA &&m) noexcept {
        Q = std::move(m.Q);
        Sigma = std::move(m.Sigma);
        q0 = std::move(m.q0);
        F = std::move(m.F);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }
};

#endif //REGEX_LAB_DFA_H
