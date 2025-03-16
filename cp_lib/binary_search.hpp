#pragma once
#include <functional>
#include <cmath>
template <typename T = long long>
T binary_search_meguru(T ok, T ng, std::function<bool(T)> check) {
    while (abs(ng - ok) > 1) {
        const auto mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        }
        else {
            ng = mid;
        }
    }
    return ok;
}


template <typename TIT, typename T>  TIT find_exact(const TIT& b, const TIT& e, const T& value) {
    auto it = std::lower_bound(b, e, value); if (it != e && !(value < *it)) {
        return it;
    }
    else {
        return e;
    }
}