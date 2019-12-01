/*
 * vecmap - fast map using lower_bound and vector<pair<Key,T>>
 *
 * This software is released into the public domain.
 */

#pragma once

#include <vector> // std::vector
#include <utility> // std::pair
#include <iterator> // std::begin, std::end
#include <algorithm> // std::lower_bound
#include <functional> // std::less

template <class Key, class T, class Compare = std::less<Key>>
struct vecmap
{
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<Key,T> value_type;

    std::vector<value_type> data;

    auto begin() { return std::begin(data); }
    auto end() { return std::end(data); }

    T& operator[](const Key &key)
    {
        auto c = Compare();
        auto i = std::lower_bound(begin(), end(), key,
            [&c](const value_type &l, const Key &k) { return c(l.first, k); });
        if (i == data.end() || c(key, i->first)) {
            i = data.insert(i, value_type(key, T()));
        }
        return i->second;
    }
};
