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

std::vector<long long> factorials(int n) {
    std::vector<long long> factorial(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    return factorial;
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

/// <summary>
/// MODULOÇÃaÇÃêœÇÃãtå≥
/// </summary>
/// <param name="a"></param>
/// <param name="modulo"></param>
/// <returns></returns>
long long modinv(long long a, long long modulo) {
    long long b = modulo, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; std::swap(a, b);
        u -= t * v; std::swap(u, v);
    }
    u %= modulo;
    if (u < 0) u += modulo;
    return u;
}



static vector<int> prime_enumerate(int N) {
    vector<bool> is_prime(N + 1, true);
    vector<int> primes;
    if (N < 2) return primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) is_prime[j] = false;
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}
static long long pow_modulo(long long base, long long p, long long modulo) {
    long long result = 1;
    base %= modulo;
    while (p > 0) {
        if (p % 2 == 1) {
            result = (result * base) % modulo;
        }
        base = (base * base) % modulo;
        p /= 2;
    }
    return result;
}
static long long power(long long base, long long exponent, long long MODULO) {
    long long res = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            res = ((res * base) % MODULO);
        }
        base = (base * base) % MODULO;
        exponent /= 2;
    }
    return res;
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

vector<long long> enum_divisors(long long N) {
    vector<long long> res;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            res.push_back(i);
            if (N / i != i) res.push_back(N / i);
        }
    }
    // è¨Ç≥Ç¢èáÇ…ï¿Ç—ë÷Ç¶ÇÈ
    sort(res.begin(), res.end());
    return res;
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




static long long binomial_coefficient_capped(int n, int r, long long cap) {
    if (r < 0 || r > n) { return 0; }
    r = min(r, n - r);
    long long res = 1LL;
    for (int i = 1; i <= r; ++i) {
        if (res > (cap * i) / (n - r + i)) {
            return cap + 1;
        }
        res = res * (n - r + i) / i;
    }
    return res;
}

static long long P_capped(const vector<int>& freqs, long long cap) {
    long long ways = 1;
    long long total = accumulate(cbegin(freqs), cend(freqs), 0LL, [](long long a, int b) {return a + static_cast<long long>(b); });
    for (int c : freqs) {
        if (c == 0) { continue; }
        long long b = binomial_coefficient_capped(total, c, cap);
        if (b > cap) { return cap + 1; }
        if (ways > cap / b) { return cap + 1; }
        ways *= b;
        total -= static_cast<long long>(c);
    }
    return ways;
}

std::vector<int> comb2(MAXN);

void precompute_comb2_mod() {
    vector<long long> C(max_combs + 1);
    constexpr long long inv2 = (MODULO + 1) / 2;
    for (int i = 0; i <= max_combs; ++i) {
        C[i] = 1LL * i * (i - 1) % MODULO * inv2 % MODULO;
    }
}

template <typename T>
int popcount_kernighan(T x) {
    int count = 0;
    while (x) {
        x &= (x - 1);
        count++;
    }
    return count;
}


void combination() {
    vector<long long> C(max_combs + 1);
    constexpr long long inv2 = (MODULO + 1) / 2;
    for (int i = 0; i <= max_combs; ++i) {
        C[i] = 1LL * i * (i - 1) % MODULO * inv2 % MODULO;
    }

}


//const int max_comb = *max_element(cbegin(border_candidates), cend(border_candidates)) + 1;
//vector<long long> fac(max_comb);
//vector<long long> finv(max_comb);
//vector<long long> inv(max_comb);
//fac[0] = fac[1] = 1;
//finv[0] = finv[1] = 1;
//inv[1] = 1;
//for (int i = 2; i < max_comb; i++) {
//    fac[i] = fac[i - 1] * i % MODULO;
//    inv[i] = MODULO - inv[MODULO % i] * (MODULO / i) % MODULO;
//    finv[i] = finv[i - 1] * inv[i] % MODULO;
//}
//auto get_comb = [&](int n, int k)-> long long {
//    if (n < k) return 0;
//    if (n < 0 || k < 0) return 0;
//    return fac[n] * (finv[k] * finv[n - k] % MODULO) % MODULO;
//    };
}
