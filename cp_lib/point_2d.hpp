#pragma once
#include <vector>

namespace competitive_programming {

template <typename T>
struct point_2d {
	T y_ = 0;
	T x_ = 0;
	point_2d() :y_(0), x_(0) {}
	point_2d(T y, T x) :y_(y), x_(x) {}
	point_2d(const point_2d&) = default;
	point_2d(point_2d&&) = default;
	point_2d& operator=(const point_2d&) = default;
	point_2d& operator=(point_2d&&) = default;

	T get_y() const { return y_; }
	T get_x() const { return x_; }

	bool operator==(const point_2d& p) const {
		return y_ == p.y_ && x_ == p.x_;
	}
	bool operator < (const point_2d& p) const {
		if (y_ != p.y_) {
			return y_ < p.y_;
		}
		return x_ < p.x_;
	}

	point_2d operator +(const point_2d& p)const {
		return point_2d(y_ + p.y_, x_ + p.x_);
	}

	point_2d operator *(T a)const {
		return point_2d(y_ * a, x_ * a);
	}
};

using point_int = point_2d<int>;

const std::vector<point_int> directions4{
	point_int(-1,0),
	point_int(1,0),
	point_int(0,-1),
	point_int(0,1),
};

const  std::vector<point_int> directions8{
	point_int(-1,0),
	point_int(1,0),
	point_int(0,-1),
	point_int(0,1),
	point_int(-1,-1),
	point_int(1,1),
	point_int(1,-1),
	point_int(-1,1),
};

}