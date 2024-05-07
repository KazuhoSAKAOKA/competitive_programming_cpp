#pragma once

#include <vector>

namespace competitive_programming {


template<typename T>
struct binary_indexed_tree {

    inline static size_t lsb(size_t i) {
        return i == 0 ? 0 : i & ~(i - 1);
    }

    size_t n_;
    std::vector<T> data_;
    binary_indexed_tree(T n) : n_(n), data_(n + 1, 0) {}

    binary_indexed_tree(std::initializer_list<T> init) : n_(init.size()), data_(init.size() + 1, 0) {
        size_t i = 1;
        for (auto it = cbegin(init); it != cend(init); ++it, ++i) {
            const auto x = *it;
            data_[i] += x;
            const auto j = i + lsb(i);
            if j < table.len() {
                data_[j] += data[i];
            }
        }
    }

    void add(size_t index, T value) {
        index++;
        if (index == 0) { return; }
        for (size_t i = index; i <= n_; i += lsb(i)) {
            data_[i] += value;
        }
    }

    T get(size_t index1, size_t index2) {
        return get(index2) - get(index1);
    }

    T get(size_t index) {
        index++;
        T s(0);
        if (index == 0) { return s; }
        for (size_t i = index; i > 0; i -= lsb(i)) {
            s += data_[i];
        }
        return s;
    }
};

using fenwick_tree = binary_indexed_tree<long long>;

}