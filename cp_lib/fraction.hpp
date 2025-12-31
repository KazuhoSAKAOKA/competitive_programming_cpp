
struct fraction {
    long long numerator;
    long long denominator;
    fraction() : numerator(0), denominator(1) {}
    fraction(long long n, long long d = 1LL) : numerator(n), denominator(d) {
        if (d == 0) { throw exception(); }
        simplification();
    }
    fraction& simplification() {
        const auto gcdv = gcd(numerator, denominator);
        if (gcdv != 1) {
            numerator /= gcdv;
            denominator /= gcdv;
        }
        return *this;
    }
};
static fraction operator + (const fraction& a, const fraction& b) {
    if (a.denominator == b.denominator) {
        fraction s(a.numerator + b.numerator, a.denominator);
        s.simplification();
        return s;
    }
    else {
        const auto lcmv = lcm(a.denominator, b.denominator);
        fraction s(a.numerator * (lcmv / a.denominator) + b.numerator * (lcmv / b.denominator), lcmv);
        s.simplification();
        return s;
    }
}
static fraction operator - (const fraction& a, const fraction& b) {
    if (a.denominator == b.denominator) {
        fraction s(a.numerator - b.numerator, a.denominator);
        s.simplification();
        return s;
    }
    else {
        const auto lcmv = lcm(a.denominator, b.denominator);
        fraction s(a.numerator * (lcmv / a.denominator) - b.numerator * (lcmv / b.denominator), lcmv);
        s.simplification();
        return s;
    }
}
static fraction operator * (const fraction& a, const fraction& b) {
    if (a.numerator == 0 || b.numerator == 0) {
        return fraction(0);
    }
    fraction m(a.numerator * b.numerator, a.denominator * b.denominator);
    m.simplification();
    return m;
}
static optional<fraction> operator / (const fraction& a, const fraction& b) {
    if (b.numerator == 0) {
        return nullopt;
    }
    fraction d(a.numerator * b.denominator, a.denominator * b.numerator);
    d.simplification();
    return d;
}
static bool operator == (const fraction& a, const long long& b) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}
static bool operator == (long long& b, const fraction& a) {
    if (a.denominator != 1) { return false; }
    return a.numerator == b;
}