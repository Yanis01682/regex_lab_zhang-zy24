#ifndef REGEX_LAB_NFA_H
#define REGEX_LAB_NFA_H

#include <set>
#include <map>
#include <string>

template<typename T>
class NFA {
public:

    // NFA 的状态类型定义
    struct state {
        // 状态名，以便于调试
        std::string name;
        // 接受字符的状态转移映射
        std::map<T, std::set<state *>> transition;
        // epsilon 状态转移映射
        std::set<state *> epsilon_transition;
    };

    // 状态集
    std::set<state *> Q;

    // 输入符号集
    std::set<T> Sigma;

    // 接受字符的转移函数
    static std::set<state *> delta(state *q, T a) {
        auto it = q->transition.find(a);
        if (it != q->transition.end())
            return it->second;
        return std::set<state *>();
    };

    // epsilon 转移函数
    static std::set<state *> delta(state *q) {
        return q->epsilon_transition;
    }

    // 开始状态
    state *q0;

    // 终态集合
    std::set<state *> F;

    // 构造一个状态数量不能超过 buf_size 的 NFA
    explicit NFA(std::size_t buf_size) {
        buf = new state[buf_size];
    }

    // 存放 state 的内存空间
    state *buf;

    // 回收内存空间
    ~NFA() {
        delete[] buf;
    }

    // 禁止拷贝
    NFA(const NFA &) = delete;

    // 禁止拷贝
    NFA &operator=(const NFA &) = delete;

    // 可以移动
    NFA(NFA &&m) noexcept {
        Q = std::move(m.Q);
        Sigma = std::move(m.Sigma);
        q0 = std::move(m.q0);
        F = std::move(m.F);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }

    // 可以移动
    NFA &operator=(NFA &&m) noexcept {
        Q = std::move(m.Q);
        Sigma = std::move(m.Sigma);
        q0 = std::move(m.q0);
        F = std::move(m.F);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }
};

#endif //REGEX_LAB_NFA_H
