#ifndef REGEX_LAB_CYK_H
#define REGEX_LAB_CYK_H

#include "CFG.h"
#include "parse_tree.h"
#include <vector>
#include <map>
#include <memory>
#include <functional>

template <typename T>
ParseTree<T> CYK_algorithm(const CFG<T>& g, const std::vector<T>& str) {
    // DONE: ~80 lines
    int n = str.size();
    if (n == 0) return ParseTree<T>(); // 简单处理空串情况

    // 定义表项结构：记录生成当前变量的来源信息，用于回溯建树
    struct Record {
        int split_k;      // 切分点长度 (如果为 -1 表示是终结符产生式 A -> a)
        T left_child;     // 左孩子变量名 (或 A->a 时的 a)
        T right_child;    // 右孩子变量名 (A->a 时忽略)
        bool is_terminal; // 标记是否为 A -> a 形式
    };

    // DP 表：table[len][i][Variable] = Record
    // len: 子串长度 (1..n)
    // i: 子串起始位置 (0..n-1)
    // map key: 能生成该子串的变量名 X
    std::vector<std::vector<std::map<T, Record>>> table(n + 1, std::vector<std::map<T, Record>>(n));

    // === 1. 初始化：处理长度为 1 的子串 ===
    for (int i = 0; i < n; ++i) {
        T term = str[i];
        // 遍历所有产生式，寻找 A -> a (CNF 中 rhs 长度为 1 且为终结符)
        for (auto const& [lhs, rhs_set] : g.P) {
            for (auto const& rhs : rhs_set) {
                if (rhs.size() == 1 && rhs[0] == term) {
                    // 确认是终结符 (虽然 CNF 中长度为 1 必然是终结符，但检查一下 g.T 更稳妥)
                    if (g.T.count(rhs[0])) {
                        table[1][i][lhs] = Record{ -1, term, term, true };
                    }
                }
            }
        }
    }

    // === 2. 填表：处理长度 2 到 n ===
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            // 枚举切分点长度 k (从 1 到 len-1)
            for (int k = 1; k < len; ++k) {
                // 寻找 A -> BC
                // 左部分: table[k][i], 右部分: table[len-k][i+k]
                for (auto const& [lhs, rhs_set] : g.P) {
                    for (auto const& rhs : rhs_set) {
                        if (rhs.size() == 2) {
                            T B = rhs[0];
                            T C = rhs[1];
                            // 检查 B 和 C 是否分别存在于左右子表的对应位置
                            if (table[k][i].count(B) && table[len - k][i + k].count(C)) {
                                // 记录路径：A -> B C (切分点 k)
                                table[len][i][lhs] = Record{ k, B, C, false };
                            }
                        }
                    }
                }
            }
        }
    }

    // === 3. 回溯建树 ===
    ParseTree<T> tree;
    // 检查是否有 S 能生成整个串 (长度 n, 起始 0)
    if (table[n][0].count(g.S)) {
        using Node = typename ParseTree<T>::node;

        // 递归构建函数的 Lambda
        std::function<std::shared_ptr<Node>(T, int, int, std::shared_ptr<Node>)> construct = 
            [&](T var, int len, int i, std::shared_ptr<Node> parent) -> std::shared_ptr<Node> {
            
            // 创建当前变量节点
            auto node_ptr = std::make_shared<Node>(Node::LabelType::Variable, var, parent);
            
            // 获取记录的来源信息
            Record rec = table[len][i][var];
            
            if (rec.is_terminal) {
                // 情况 A: A -> a
                // 创建终结符子节点
                auto term_node = std::make_shared<Node>(Node::LabelType::Terminal, rec.left_child, node_ptr);
                node_ptr->children.push_back(term_node);
            } else {
                // 情况 B: A -> BC
                // 递归构建左孩子 B (长度 k, 起始 i)
                node_ptr->children.push_back(construct(rec.left_child, rec.split_k, i, node_ptr));
                // 递归构建右孩子 C (长度 len-k, 起始 i+k)
                node_ptr->children.push_back(construct(rec.right_child, len - rec.split_k, i + rec.split_k, node_ptr));
            }
            return node_ptr;
        };
        
        // 从 S 开始构建
        tree.root = construct(g.S, n, 0, nullptr);
    }

    return tree;
}

#endif // REGEX_LAB_CYK_H
