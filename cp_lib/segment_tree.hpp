#pragma once

#include <vector>
#include <functional>

namespace competitive_programming {

template <typename T, typename Q>
struct segment_tree {
	T inf_;
	std::vector<std::vector<T>> data_;
	Q query_;

	segment_tree(size_t n, Q query, T inf) :query_(query) ,inf_(inf) {
		allocate_buffer(n);
	}
	template<typename Container>
	segment_tree(Container& source, Q query, T inf) :query_(query), inf_(inf) {
		const size_t n = source.size();
		allocate_buffer(n);
		build(cbegin(source), cend(source));
	}

	void allocate_buffer(size_t n) {
		size_t count = 1;
		for (;;) {
			data_.emplace_back(std::vector<T>(count, inf_));
			if (n <= count) {
				break;
			}
			count *= 2;
		}
	}

	template<typename IT> 
	void build(IT begin, IT end) {
		size_t index = 0;
		for (auto it = begin; it != end; ++it) {
			data_[data_.size() - 1][index++] = *it;
		}
		for (size_t depth_index = data_.size() - 1; depth_index > 0; depth_index--) {
			const auto& source = data_[depth_index];
			auto& destination = data_[depth_index - 1];
			for (size_t i = 0; i < destination.size(); i++) {
				destination[i] = query_(source[i * 2], source[i * 2 + 1]);
			}
		}
	}

	void update(size_t index, T value) {
		data_[data_.size() - 1][index] = value;
		for(size_t depth_index = data_.size() - 1; depth_index > 0; --depth_index) {
			index /= 2;
			data_[depth_index - 1][index] = query_(data_[depth_index][index * 2], data_[depth_index][index * 2 + 1]);
		}
	}

	T query(size_t a, size_t b) {
		return query(a, b, 0, 0, 0, data_.back().size());
	}

	T query(size_t a, size_t b, size_t depth_index, size_t index, size_t l, size_t r) {
		if (r <= a || b <= l) {
			return inf_; 
		}
		if (a <= l && r <= b) {
			return data_[depth_index][index];
		}
		const auto left = query(a, b, depth_index + 1, index * 2, l, (l + r) / 2);
		const auto right = query(a, b, depth_index + 1, index * 2 + 1, (l + r) / 2, r);
		return query_(left, right);
	}


};

template <typename T = long long>
struct seqment_tree_range_maximum_query : public segment_tree<T, std::function<T(T, T)>> {
	seqment_tree_range_maximum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	template <typename Container>
	seqment_tree_range_maximum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
};
template <typename T = long long>
struct seqment_tree_range_minimum_query : public segment_tree<T, std::function<T(T, T)>> {
	seqment_tree_range_minimum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	template <typename Container>
	seqment_tree_range_minimum_query(Container source) :segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
};

template <typename T = long long>
struct seqment_tree_sum_query : public segment_tree<T, std::function<T(T, T)>> {
	seqment_tree_sum_query(size_t n) :segment_tree<T, std::function<T(T, T)>>(n, [](T a, T b) {return a + b; }, 0) {}
	template <typename Container>
	seqment_tree_sum_query(Container source) : segment_tree<T, std::function<T(T, T)>>(source, [](T a, T b) {return a + b; }, 0) {}
};

template <typename T, typename Q>
struct segment_tree_2d {
	T inf_;
	std::vector<std::vector<std::vector<T>>> data_;
	Q query_;
	size_t H_;
	size_t W_;
	size_t loop_size_;

	segment_tree_2d(size_t h, size_t w, Q query, T inf) :query_(query), inf_(inf) {
		allocate_buffer(h, w);
	}
	template<typename Container>
	segment_tree_2d(Container& source, Q query, T inf) : query_(query), inf_(inf) {
		const size_t h = source.size();
		const size_t w = cbegin(source)->size();
		allocate_buffer(h, w);
		build(cbegin(source), cend(source));
	}

	static size_t pow2(size_t n) {
		if (n == 0) { return 1; }
		if (n % 2 == 1) {
			return pow2(n / 2) * pow2(n / 2) * 2;
		}
		else {
			return pow2(n / 2) * pow2(n / 2);
		}
	}

	void allocate_buffer(size_t h, size_t w) {
		size_t width_count = 1;
		size_t height_count = 1;
		size_t width_depth = 1;
		size_t height_depth = 1;

		while (height_count < h) {
			height_count *= 2;
			height_depth++;
		}
		while (width_count < w) {
			width_count *= 2;
			width_depth++;
		}

		size_t width_size;
		size_t height_size;
		if (width_depth < height_depth) {
			width_size = 1;
			height_size = pow2(height_depth - width_depth);
			loop_size_ = height_size;
		}
		else {
			height_size = 1;
			width_size = pow2(width_depth - height_depth);
			loop_size_ = width_size;
		}
		for (size_t depth_index = 0; depth_index < std::min(height_depth, width_depth); depth_index++) {
			data_.emplace_back(std::vector<std::vector<T>>(height_size, std::vector<T>(width_size, inf_)));
			width_size *= 2;
			height_size *= 2;
		}
		H_ = data_.back().size();
		W_ = data_.back().front().size();
	}

	template<typename IT>
	void build(IT begin, IT end) {
		size_t height_index = 0;
		auto& matrix = data_[data_.size() - 1];
		for (auto ith = begin; ith != end; ++ith) {
			size_t width_index = 0;
			for (auto itw = cbegin(*ith); itw != cend(*ith); ++itw) {
				matrix[height_index][width_index++] = *itw;
			}
			height_index++;
		}
		for (size_t depth_index = data_.size() - 1; depth_index > 0; depth_index--) {
			const auto& source = data_[depth_index];
			auto& destination = data_[depth_index - 1];
			for (size_t i = 0; i < destination.size(); i++) {
				for (size_t j = 0; j < destination.front().size(); j++) {
					destination[i][j] =
						query_(
							query_(source[i * 2][j * 2], source[i * 2 + 1][j * 2]),
							query_(source[i * 2][j * 2 + 1], source[i * 2 + 1][j * 2 + 1]));
				}
			}
		}
	}




	void update(size_t height_index, size_t width_index, T value) {
		data_[data_.size() - 1][height_index][width_index] = value;
		for (size_t depth_index = data_.size() - 1; depth_index > 0; --depth_index) {
			height_index /= 2;
			width_index /= 2;
			const auto h = height_index * 2;
			const auto w = width_index * 2;
			const auto& source = data_[depth_index];
			data_[depth_index - 1][index] =
				query_(
					query_(source[h][w], source[h][w + 1]),
					query_(source[h + 1][w], source[h + 1][w + 1]));
		}
	}


	T query(size_t height_begin, size_t width_begin, size_t height_end, size_t width_end) {
		if (H_ < W_) {
			T res = inf_;
			for (size_t i = 0; i < loop_size_; i++) {
				res = query_(res,
					query(height_begin, width_begin, height_end, width_end,
						0, 0, i,
						0, i *H_, H_, (i + 1) * H_)
					);
			}
			return res;
		}
		else {
			T res = inf_;
			for (size_t i = 0; i < loop_size_; i++) {
				res = query_(res,
					query(height_begin, width_begin, height_end, width_end,
						0, i, 0,
						i * W_, 0, (i + 1) * W_, W_)
				);
			}
			return res;
		}
	}

	T query(size_t height_begin, size_t width_begin, size_t height_end, size_t width_end, 
		size_t depth_index, size_t height_index, size_t width_index,
		size_t height_top, size_t width_left, size_t height_bottom, size_t width_right) {
		if (height_bottom <= height_begin || height_end <= height_top || width_right <= width_begin || width_end <= width_left) {
			return inf_;
		}

		if (height_begin <= height_top && height_bottom <= height_end && width_begin <= width_left && width_right <= width_end) {
			return data_[depth_index][height_index][width_index];
		}

		const auto left_top = query(height_begin, width_begin, height_end, width_end, 
			depth_index + 1, height_index * 2, width_index * 2, 
			height_top, width_left, (height_top + height_bottom) / 2, (width_left + width_right) / 2);

		const auto left_bottom = query(height_begin, width_begin, height_end, width_end, 
			depth_index + 1, height_index * 2 + 1, width_index * 2, 
			(height_top + height_bottom) / 2, width_left, height_bottom, (width_left + width_right) / 2);

		const auto right_top = query(height_begin, width_begin, height_end, width_end, 
			depth_index + 1, height_index * 2, width_index * 2 + 1, 
			height_top, (width_left + width_right) / 2, (height_top + height_bottom) / 2, width_right);

		const auto right_bottom = query(height_begin, width_begin, height_end, width_end, 
			depth_index + 1, height_index * 2 + 1, width_index * 2 + 1, 
			(height_top + height_bottom) / 2, (width_left + width_right) / 2, height_bottom, width_right);
		
		return query_(query_(left_top, left_bottom), query_(right_top, right_bottom));
	}

};


template <typename T = long long>
struct seqment_tree_2d_range_maximum_query : public segment_tree_2d<T, std::function<T(T, T)>> {
	seqment_tree_2d_range_maximum_query(size_t h, size_t w) :segment_tree_2d(n, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
	template <typename Container>
	seqment_tree_2d_range_maximum_query(Container source) : segment_tree_2d(source, [](T a, T b) {return std::max(a, b); }, std::numeric_limits<T>::min()) {}
};
template <typename T = long long>
struct seqment_tree_2d_range_minimum_query : public segment_tree_2d<T, std::function<T(T, T)>> {
	seqment_tree_2d_range_minimum_query(size_t h, size_t w) :segment_tree_2d(n, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
	template <typename Container>
	seqment_tree_2d_range_minimum_query(Container source) : segment_tree_2d(source, [](T a, T b) {return std::min(a, b); }, std::numeric_limits<T>::max()) {}
};



}
/*
template <typename T, typename Q>
struct segment_tree {
    const T INF_;
    int n_;
    vector<T> dat_;
    Q query_;
    segment_tree(int n, Q query, T inf) : n_(n), dat(n * 4, inf), query_(query), INF_(inf){
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n_ = x;
    }
    void update(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = query_(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return INF;
        }
        else if (a <= l && r <= b) {
            return dat[k];
        }
        else {
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return query_(vl, vr);
        }
    }
};
static int add(int a, int b) { return a + b; }
using segment_tree_sum = segment_tree<int, decltype(add)>;*/


template <typename T, typename F>
struct SegmentTree2D {
private:
	int id(int h, int w) const { return h * 2 * W + w; }

public:
	int H, W;
	vector<T> seg;
	const F f;
	const T I;

	SegmentTree2D(int h, int w, F _f, const T& i) : f(_f), I(i) { init(h, w); }

	void init(int h, int w) {
		H = W = 1;
		while (H < h) H <<= 1;
		while (W < w) W <<= 1;
		seg.assign(4 * H * W, I);
	}

	// build ‚É‚Ì‚ÝŒÄ‚Ô
	void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

	void build() {
		// w in [W, 2W)
		for (int w = W; w < 2 * W; w++) {
			for (int h = H - 1; h; h--) {
				seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]);
			}
		}
		// h in [0, 2H)
		for (int h = 0; h < 2 * H; h++) {
			for (int w = W - 1; w; w--) {
				seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]);
			}
		}
	}

	T get(int h, int w) const { return seg[id(h + H, w + W)]; }
	T operator()(int h, int w) const { return seg[id(h + H, w + W)]; }

	void update(int h, int w, const T& x) {
		h += H, w += W;
		seg[id(h, w)] = x;
		for (int i = h >> 1; i; i >>= 1) {
			seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]);
		}
		for (; h; h >>= 1) {
			for (int j = w >> 1; j; j >>= 1) {
				seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]);
			}
		}
	}

	T _inner_query(int h, int w1, int w2) {
		T res = I;
		for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
			if (w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
			if (w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
		}
		return res;
	}

	// [ (h1,w1), (h2,w2) ) ”¼ŠJ
	T query(int h1, int w1, int h2, int w2) {
		if (h1 >= h2 || w1 >= w2) return I;
		T res = I;
		h1 += H, h2 += H, w1 += W, w2 += W;
		for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
			if (h1 & 1) res = f(res, _inner_query(h1, w1, w2)), h1++;
			if (h2 & 1) --h2, res = f(res, _inner_query(h2, w1, w2));
		}
		return res;
	}
};