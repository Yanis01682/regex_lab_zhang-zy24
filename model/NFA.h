#ifndef REGEX_LAB_NFA_H
#define REGEX_LAB_NFA_H

#include <memory>
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
        std::map<T, std::set<std::shared_ptr<state>>> transition;
        // epsilon 状态转移映射
        std::set<std::shared_ptr<state>> epsilon_transition;
    };

    // 状态集
    std::set<std::shared_ptr<state>> Q;

    // 输入符号集
    std::set<T> Sigma;

    // 接受字符的转移函数
    static std::set<std::shared_ptr<state>> delta(std::shared_ptr<state> q, T a) {
        auto it = q->transition.find(a);
        if (it != q->transition.end())
            return it->second;
        return std::set<std::shared_ptr<state>>();
    };

    // epsilon 转移函数
    static std::set<std::shared_ptr<state>> delta(std::shared_ptr<state> q) {
        return q->epsilon_transition;
    }

    // 开始状态
    std::shared_ptr<state> q0;

    // 终态集合
    std::set<std::shared_ptr<state>> F;

    // 构造一个 NFA
    explicit NFA() = default;

    // 回收内存空间
    ~NFA() = default;

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
    }

    // 可以移动
    NFA &operator=(NFA &&m) noexcept {
        Q = std::move(m.Q);
        Sigma = std::move(m.Sigma);
        q0 = std::move(m.q0);
        F = std::move(m.F);
    }
};

#endif //REGEX_LAB_NFA_H
