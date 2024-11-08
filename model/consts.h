//
// Created by 张英奇 on 2023/9/25.
//

#ifndef REGEX_LAB_CONSTS_H
#define REGEX_LAB_CONSTS_H

#include <cwchar>
#include <string>
#include "COE.h"

template<typename T>
constexpr T regex_union;
template<typename T>
constexpr T regex_concatenation;
template<typename T>
constexpr T regex_closure;
template<typename T>
constexpr T left_parenthesis;
template<typename T>
constexpr T right_parenthesis;
template<typename T>
constexpr T epsilon;

template<> constexpr char regex_union<char> = '+';
template<> constexpr char regex_concatenation<char> = '-';
template<> constexpr char regex_closure<char> = '*';
template<> constexpr char left_parenthesis<char> = '(';
template<> constexpr char right_parenthesis<char> = ')';
template<> constexpr char epsilon<char> = '\0';

template<> constexpr wchar_t regex_union<wchar_t> = '+';
template<> constexpr wchar_t regex_concatenation<wchar_t> = '-';
template<> constexpr wchar_t regex_closure<wchar_t> = '*';
template<> constexpr wchar_t left_parenthesis<wchar_t> = '(';
template<> constexpr wchar_t right_parenthesis<wchar_t> = ')';
template<> constexpr wchar_t epsilon<wchar_t> = '\0';

template<> const std::string regex_union<std::string> = "regex_union";
template<> const std::string regex_concatenation<std::string> = "regex_concatenation";
template<> const std::string regex_closure<std::string> = "regex_closure";
template<> const std::string left_parenthesis<std::string> = "left_parenthesis";
template<> const std::string right_parenthesis<std::string> = "right_parenthesis";
template<> const std::string epsilon<std::string> = "epsilon";

template<> constexpr COE regex_union<COE> = {'+', false};
template<> constexpr COE regex_concatenation<COE> = {'-', false};
template<> constexpr COE regex_closure<COE> = {'*', false};
template<> constexpr COE left_parenthesis<COE> = {'(', false};
template<> constexpr COE right_parenthesis<COE> = {')', false};
template<> constexpr COE epsilon<COE> = {'\0', true};


#endif //REGEX_LAB_CONSTS_H
