//
// Created by Z_150 on 2023/9/27.
//

#ifndef REGEX_LAB_SOLUTION_MERGE_NFA_H
#define REGEX_LAB_SOLUTION_MERGE_NFA_H

#include <algorithm>
#include "NFA.h"

template<typename T>
NFA<T> merge_NFA(const NFA<T> &n1, const NFA<T> &n2,
                 unsigned long long addition, typename NFA<T>::state **a,
                 typename NFA<T>::state *&q01, typename NFA<T>::state *&f1,
                 typename NFA<T>::state *&q02, typename NFA<T>::state *&f2) {
    NFA<T> nfa(n1.Q.size() + n2.Q.size() + addition);
    for (unsigned long long i = 0; i < addition; ++i) {
        a[i] = &nfa.buf[i];
        nfa.Q.insert(a[i]);
    }
    typename NFA<T>::state *start = nfa.buf + addition;
    long long distance = reinterpret_cast<char *>(start) - reinterpret_cast<char *>(n1.buf);
    q01 = reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(n1.q0) + distance);
    f1 = reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(*n1.F.begin()) + distance);
    for (unsigned long long i = 0; i < n1.Q.size(); ++i) {
        start[i].name = n1.buf[i].name;
        for (auto &&j: n1.buf[i].transition)
            for (auto &&k: j.second)
                start[i].transition[j.first].insert(
                        reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(k) + distance));
        for (auto &&j: n1.buf[i].epsilon_transition)
            start[i].epsilon_transition.insert(
                    reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(j) + distance));
        nfa.Q.insert(&start[i]);
    }
    start += n1.Q.size();
    distance = reinterpret_cast<char *>(start) - reinterpret_cast<char *>(n2.buf);
    q02 = reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(n2.q0) + distance);
    f2 = reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(*n2.F.begin()) + distance);
    for (unsigned long long i = 0; i < n2.Q.size(); ++i) {
        start[i].name = n2.buf[i].name;
        for (auto &&j: n2.buf[i].transition)
            for (auto &&k: j.second)
                start[i].transition[j.first].insert(
                        reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(k) + distance));
        for (auto &&j: n2.buf[i].epsilon_transition)
            start[i].epsilon_transition.insert(
                    reinterpret_cast<typename NFA<T>::state *>(reinterpret_cast<char *>(j) + distance));
        nfa.Q.insert(&start[i]);
    }
    std::set_union(n1.Sigma.begin(), n1.Sigma.end(),
                   n2.Sigma.begin(), n2.Sigma.end(),
                   std::inserter(nfa.Sigma, nfa.Sigma.begin()));
    return nfa;
}

#endif //REGEX_LAB_SOLUTION_MERGE_NFA_H
