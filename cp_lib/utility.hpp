
static int get_msb(int num) {
	int position = -1;
	while (num > 0) {
		num >>= 1;
		position++;
	}
	return position;
}


int main() {

	long long N;
	cin >> N;
	string T;
	cin >> T;
	map<int, long long> freq;
	freq[0] = 1;
	int prefix = 0;
	long long result = 0;
	for (long long i = 0; i < N; i++) {
		if (T[i] == '0') {
			prefix ^= 1;
		}
		result += freq[prefix];
		freq[prefix]++;
	}
	cout << result << endl;
	return 0;
}


template <typename T>
static int popcount_kernighan(T x) {
	int count = 0;
	while (x) {
		x &= (x - 1);
		count++;
	}
	return count;
}

