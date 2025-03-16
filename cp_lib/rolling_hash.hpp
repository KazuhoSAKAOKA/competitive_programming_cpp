#pragma once
#include <vector>
#include <string>

static std::vector<long long> init_powers(int N, long long b, long long modulo) {
    std::vector<long long> powers(N + 1);
    powers[0] = 1;
    for (int i = 0; i < N; i++) {
        powers[i + 1] = (powers[i] * b) % modulo;
    }

    return powers;
}

static std::vector<long long> rolling_hash(const std::string& s, long long b, long long modulo) {
    const auto N = size(s);
    std::vector<long long> hash(N + 1);
    for (int i = 0; i < N; i++)
    {
        hash[i + 1] = (hash[i] * b + s[i]) % modulo;
    }
    return hash;
}

static long long get_hash(const std::vector<long long>& rolling_hash, const std::vector<long long>& powers, long long modulo, int l, int r) {
    auto hash_value = rolling_hash[r] - (rolling_hash[l] * powers[r - l] % modulo);
    if (hash_value < 0) { hash_value += modulo; }
    return hash_value;
}