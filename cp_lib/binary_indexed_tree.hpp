#pragma once

#include <vector>

namespace competitive_programming {

//
//template<typename T>
//struct binary_indexed_tree {
//
//    inline static size_t lsb(size_t i) {
//        return i == 0 ? 0 : i & ~(i - 1);
//    }
//
//    size_t n;
//    vector<T> data;
//    //コンストラクタ
//    binary_indexed_tree(size_t n) :n(n), data(n + 1, 0) {}
//
//    void add(size_t i, T x) {
//        i++;
//        if (i == 0) return;
//        for (size_t k = i; k <= n; k += (k & -k)) {
//            data[k] += x;
//        }
//    }
//
//    T sum(size_t i, size_t j) {
//        return sum_sub(j) - sum_sub(i - 1);
//    }
//
//    T sum_sub(size_t i) {
//        i++;
//        T s = 0;
//        if (i == 0) return s;
//        for (size_t k = i; k > 0; k -= (k & -k)) {
//            s += data[k];
//        }
//        return s;
//    }
//
//    size_t lower_bound(T x) {
//        if (x <= 0) {
//            //xが0以下の場合は該当するものなし→0を返す
//            return 0;
//        }
//        else {
//            size_t i = 0; size_t r = 1;
//            //最大としてありうる区間の長さを取得する
//            //n以下の最小の二乗のべき(BITで管理する数列の区間で最大のもの)を求める
//            while (r < n) r = r << 1;
//            //区間の長さは調べるごとに半分になる
//            for (int len = r; len > 0; len = len >> 1) {
//                //その区間を採用する場合
//                if (i + len < n && data[i + len] < x) {
//                    x -= data[i + len];
//                    i += len;
//                }
//            }
//            return i;
//        }
//    }
//};
//


template<typename T>
class binary_indexed_tree {
    int n;
    std::vector<T> data;

public:
    binary_indexed_tree(int size) : n(size), data(size + 1, 0) {}

    // i番目にxを加算（0-indexed）
    void add(int i, T x) {
        ++i; // 1-indexedに変換
        while (i <= n) {
            data[i] += x;
            i += i & -i;
        }
    }

    // [0, i) の累積和（0-indexed）
    T sum(int i) const {
        T res = 0;
        while (i > 0) {
            res += data[i];
            i -= i & -i;
        }
        return res;
    }

    // [l, r) の累積和（0-indexed）
    T sum(int l, int r) const {
        return sum(r) - sum(l);
    }
};

using fenwick_tree = binary_indexed_tree<long long>;

}