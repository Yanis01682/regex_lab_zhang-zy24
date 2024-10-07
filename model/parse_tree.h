//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_PARSE_TREE_H
#define REGEX_LAB_PARSE_TREE_H

#include <vector>

template<typename T>
// 正则表达式的语法分析树
class ParseTree {
public:

    // 语法分析树的节点类型
    struct Node {
        // 节点的类型枚举
        enum LabelType {
            // 变元
            Variable = 0,
            // 终结符
            Terminal = 1,
            // epsilon
            Epsilon = 2,
        };
        // 节点的类型
        LabelType label_type;
        // 节点的内容
        T label_value;
        // 父节点
        Node *parent;
        // 各子节点
        std::vector<Node *> children;
    };

    // 语法分析树的根节点
    Node *root;

    // 构造一个节点数量不能超过 buf_size 的语法分析树
    explicit ParseTree(unsigned long long buf_size) {
        buf = new Node[buf_size];
    }

    // 存放 node 的内存空间
    Node *buf;

    // 回收内存空间
    ~ParseTree() {
        delete[] buf;
    }

    // 禁止拷贝
    ParseTree(const ParseTree &) = delete;

    // 禁止拷贝
    ParseTree &operator=(const ParseTree &) = delete;

    // 可以移动
    ParseTree(ParseTree &&m) noexcept {
        root = std::move(m.root);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }

    // 可以移动
    ParseTree &operator=(ParseTree &&m) noexcept {
        root = std::move(m.root);
        buf = std::move(m.buf);
        m.buf = nullptr;
    }
};


#endif //REGEX_LAB_PARSE_TREE_H
