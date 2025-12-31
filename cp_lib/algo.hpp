#pragma once
#include <vector>

namespace competitive_programming {


/// <summary>
/// 過半数を取っているマジョリティ検索。
/// ※count < n / 2の場合は正しくない
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"></param>
/// <returns></returns>
template <typename T>
static std::pair<T, size_t> boyer_moore_majority_voting(const std::vector<T>& arr) {
    T candidate = arr[0];
    size_t votes = 1;
    for (int i = 1; i < size(arr); i++) {
        const auto& v = arr[i];
        if (votes == 0) {
            candidate = v;
            votes = 1;
        }
        else {
            if (v == candidate) {
                votes++;
            }
            else {
                votes--;
            }
        }
    }
    size_t count = count_if(cbegin(arr), cend(arr), [&](const T& v) { return v == candidate; });
    return { candidate, count };
}




static vector<int> manacher_even(const string& original) {
    const auto n_original = size(original);
    string s(2 * n_original + 1, '#');
    for (int i = 0; i < n_original; i++) { s[2 * i + 1] = original[i]; }
    const auto n = 2 * n_original + 1;
    vector<int> rad(n);
    int c = 0, r = 0;
    while (c < n) {
        while (0 <= c - r && c + r < n && s[c - r] == s[c + r]) r++;
        rad[c] = r;
        int k = 1;
        while (0 <= c - k && k + rad[c - k] < r) {
            rad[c + k] = rad[c - k];
            k++;
        }
        c += k;
        r -= k;
    }
    vector<int> radeven(size(original));

    for (int i = 0; i < n_original; i++) {
        radeven[i] = rad[i * 2] / 2;
    }
    return radeven;
}

static vector<int> manacher_odd(const string& original) {
    int n = size(original);
    vector<int> rad(n);
    int c = 0, r = 0;

    while (c < n) {
        while (0 <= c - r && c + r < n && original[c - r] == original[c + r]) { r++; }
        rad[c] = r;
        int k = 1;
        while (0 <= c - k && k + rad[c - k] < r) {
            rad[c + k] = rad[c - k];
            k++;
        }
        c += k;
        r -= k;
    }
    return rad;
}



//最小交換回数
static int get_cycle(vector<bool>& visited, const vector<int>& indexes, int start) {
    int s = 0;
    int current = start;
    while (!visited[current]) {
        visited[current] = true;
        current = indexes[current];
        s++;
    }

    return s;
}
}
