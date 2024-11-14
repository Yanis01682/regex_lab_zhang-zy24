#ifndef REGEX_LAB_PARSE_TREE_H
#define REGEX_LAB_PARSE_TREE_H

#include <memory>
#include <vector>

template<typename T>
// 正则表达式的语法分析树
class ParseTree {
public:

    // 语法分析树的节点类型
    struct node {
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
        std::shared_ptr<node> parent;
        // 各子节点，按照语法分析树丛左到右的顺序
        std::vector<std::shared_ptr<node>> children;

        // 构造一个不含子节点的语法分析树节点
        explicit node(LabelType label_type, T label_value, std::shared_ptr<node> parent) :
                label_type(label_type), label_value(label_value), parent(parent), children({}) {}
    };

    // 语法分析树的根节点
    std::shared_ptr<node> root;

    // 构造一个语法分析树
    explicit ParseTree() = default;

    // 回收内存空间
    ~ParseTree() = default;

    // 禁止拷贝
    ParseTree(const ParseTree &) = delete;

    // 禁止拷贝
    ParseTree &operator=(const ParseTree &) = delete;

    // 可以移动
    ParseTree(ParseTree &&m) noexcept {
        root = std::move(m.root);
    }

    // 可以移动
    ParseTree &operator=(ParseTree &&m) noexcept {
        root = std::move(m.root);
        return *this;
    }
};


#endif //REGEX_LAB_PARSE_TREE_H
