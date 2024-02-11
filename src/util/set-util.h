#ifndef SET_UTIL_H
#define SET_UTIL_H

#include <set>

inline std::set<char> merge_sets(const std::set<char> &a, const std::set<char> &b) {
    std::set<char> set{a.cbegin(), a.cend()};
    set.insert(b.cbegin(), b.cend());
    return set;
}

#endif //SET_UTIL_H
