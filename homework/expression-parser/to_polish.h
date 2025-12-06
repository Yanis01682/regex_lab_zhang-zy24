#ifndef REGEX_LAB_TO_POLISH_H
#define REGEX_LAB_TO_POLISH_H

#include "consts.h"
#include <string>
#include <vector>

template <typename T>
std::vector<T> to_polish(const std::vector<T>& regex) {
    std::vector<T> r, next;
    std::size_t j = 0;
    for (int i = 0; i < regex.size(); ++i) {
        T c = regex[i];
        if (c == regex_union<T>) {
            r.insert(r.end(), next.begin(), next.end());
            next.clear();
            r.insert(r.begin(), c);
            j = r.size();
        } else if (c == regex_closure<T>) {
            next.insert(next.begin(), c);
        } else if (c == left_parenthesis<T>) {
            r.insert(r.end(), next.begin(), next.end());
            int rp = i, depth = 1;
            while (depth > 0) {
                rp++;
                if (regex[rp] == left_parenthesis<T>) {
                    depth++;
                }
                if (regex[rp] == right_parenthesis<T>) {
                    depth--;
                }
            }
            next = to_polish(std::vector<T>(&regex.data()[i + 1], &regex.data()[rp]));
            if (i != 0 && regex[i - 1] != regex_union<T>) {
                r.insert(r.begin() + j, regex_concatenation<T>);
            }
            j = r.size();
            i = rp;
        } else {
            r.insert(r.end(), next.begin(), next.end());
            next.clear();
            next.push_back(c);
            if (i != 0 && regex[i - 1] != regex_union<T>) {
                r.insert(r.begin() + j, regex_concatenation<T>);
            }
            j = r.size();
        }
    }
    r.insert(r.end(), next.begin(), next.end());
    return r;
}

template <typename T>
std::vector<T> to_polish(const std::basic_string<T>& s) {
    std::vector<T> v(s.begin(), s.end());
    return to_polish(v);
}

#endif // REGEX_LAB_TO_POLISH_H
