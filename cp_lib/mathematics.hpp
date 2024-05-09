#pragma once


namespace competitive_programming {

template <typename T>
T gcd(const T a, const T b) {
	if (b == 0) { return a; }
	return gcd(b, a % b);
}

template <typename T>
T lcm(const T a, const T b) {
	return a / gcd(a, b) * b;
}


}
