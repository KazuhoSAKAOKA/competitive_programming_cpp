#pragma once
#include <vector>
#include <string>

namespace competitive_programming {

template <typename T>
T gcd(const T& a, const T& b) {
	if (b == 0) { return a; }
	return gcd(b, a % b);
}

template <typename T>
T lcm(const T& a, const T& b) {
	return a / gcd(a, b) * b;
}


static std::vector<bool> eratosthenes(int n) {
    std::vector<bool> candidates(n + 1, true);
    candidates[0] = false;
    candidates[1] = false;
    const auto limit = sqrt(n);
    int current = 2;
    while (current <= limit) {
        if (candidates[current]) {
            for (int i = 2; i * current <= n; i++) {
                candidates[i * current] = false;
            }
        }
        current++;
    }
    return candidates;
}


std::vector<long long> divisor(long long n) {
    std::vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) { ret.push_back(n / i); }
        }
    }
    //sort(ret.begin(), ret.end());
    return ret;
}
template <typename T>
inline bool intersect(const T& x1, const T& x2) {

}


static bool divisble2(const std::string& s, size_t offset, size_t length) {
    if (length == 1) {
        return s[offset + length - 1] == '5';
    }
    return s[offset + length - 1] == '5' || s[offset + length - 1] == '0';
}

static bool divisble3(const std::string& s, size_t offset, size_t length) {
    long long cur_sum = 0;
    for (size_t i = 0; i < length; i++) {
        cur_sum += static_cast<long long>(s[i+offset] - '0');
    }
    return cur_sum % 3 == 0;
}

static bool divisble4(const std::string& s, size_t offset, size_t length) {
    long long count = 0;
    if (length < 2) {
        return s[offset + length - 1] == '4' || s[offset + length - 1] == '8';
    }
    const auto v = s.substr(length - 2, 2);
    const auto value = std::stoi(v);
    return  value % 4 == 0;
}
static bool divisble5(const std::string& s, size_t offset, size_t length) {
    if (length == 1) {
        return s[offset + length - 1] == '5';
    }
    return s[offset + length - 1] == '5' || s[offset + length - 1] == '0';
}

static long long divisble6(const std::string& s, size_t offset, size_t length) {
    return divisble2(s, offset, length) && divisble3(s, offset, length);
}

static bool divisble7(const std::string& s, int offset, int length) {
    long long even_groups = 0;
    long long odd_groups = 0;
    for (int i = 0; i < (length + 2) / 3; i++) {
        auto index = length - (i + 1) * 3;
        auto len = 3;
        if (index < 0) {
            len += index;
            index = 0;
        }
        const auto temp = s.substr(offset + index, len);
        const auto value = stoi(temp);
        if (i % 2 == 0) {
            even_groups += value;
        }
        else {
            odd_groups += value;
        }
    }

    const auto diff = std::max(even_groups, odd_groups) - std::min(even_groups, odd_groups);
    return (diff % 7) == 0;
}

static bool divisble8(const std::string& s, int offset, int length) {
    long long count = 0;
    if (length >= 3) {
        const auto v = s.substr(length - 3, 3);
        const auto value = std::stoi(v);
        return value % 8;
    }
    if (length >= 2) {
        const auto v = s.substr(length - 2, 2);
        const auto value = stoi(v);
        return value % 8;
    }
    return s[length - 1] == '8';
}

static bool divisble9(const std::string& s, int offset, int length) {
    long long cur_sum = 0;
    for (int i = 0; i < length; i++) {
        int index = length - 1 - i;
        cur_sum += static_cast<long long>(s[index] - '0');
    }
    return cur_sum % 9 == 0;
}



}
