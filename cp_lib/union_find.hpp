#pragma once

#include <vector>

namespace competitive_programming {

struct union_find {

    std::vector<size_t> parents_;
    std::vector<size_t> sizes_;

    union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
        for (size_t i = 0; i < n; i++) {
            parents_[i] = i;
        }
    }

    size_t root(size_t x) {
        if (x == parents_[x]) { return x; }
        parents_[x] = root(parents_[x]);
        return parents_[x];
    }

    bool same(size_t x, size_t y) {
        return root(x) == root(y);
    }

    void unite(size_t x, size_t y) {
        const auto rootx = root(x);
        const auto rooty = root(y);
        if (rootx == rooty) { return; }
        if (sizes_[rootx] < sizes_[rooty]) {
            parents_[rootx] = rooty;
            sizes_[rooty] += sizes_[rootx];
        }
        else {
            parents_[rooty] = rootx;
            sizes_[rootx] += sizes_[rooty];
        }
    }

    size_t size(size_t x) {
        return sizes_[root(x)];
    }

    bool is_root(size_t x) {
        return root(x) == x;
    }
};


}