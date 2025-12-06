#ifndef REGEX_LAB_PARSER_H
#define REGEX_LAB_PARSER_H

#include "consts.h"
#include "parse_tree.h"
#include <vector>
#include <memory>
#include <functional>

template <typename T>
ParseTree<T> polish_parser(const std::vector<T>& regex) {
    // DONE: ~30 lines
    if (regex.empty()) return ParseTree<T>();

    // 1. 定义简化别名
    using Node = typename ParseTree<T>::node;
    int pos = 0; // 记录读取位置

    // 2. 定义内部递归函数 (Lambda)
    std::function<std::shared_ptr<Node>(std::shared_ptr<Node>)> build = 
        [&](std::shared_ptr<Node> parent) -> std::shared_ptr<Node> {
        
        if (pos >= regex.size()) return nullptr;
        T token = regex[pos++];

        // 构建 S 节点 (父节点)
        auto s_node = std::make_shared<Node>(Node::LabelType::Variable, T('S'), parent);
        // 构建当前符号节点 (S的第一个孩子)
        auto token_node = std::make_shared<Node>(Node::LabelType::Terminal, token, s_node);
        s_node->children.push_back(token_node);

        // 根据符号类型判断是否需要继续递归
        if (token == regex_union<T> || token == regex_concatenation<T>) {
            // 二元运算：需要两个子节点
            s_node->children.push_back(build(s_node));
            s_node->children.push_back(build(s_node));
        } else if (token == regex_closure<T>) {
            // 一元运算：需要一个子节点
            s_node->children.push_back(build(s_node));
        }
        // 其他情况(字母/Epsilon)不需要子节点，递归自动回溯

        return s_node;
    };

    // 3. 启动递归
    ParseTree<T> tree;
    tree.root = build(nullptr);
    return tree;
}

template ParseTree<char> polish_parser<char>(const std::vector<char>& regex);

#endif // REGEX_LAB_PARSER_H
