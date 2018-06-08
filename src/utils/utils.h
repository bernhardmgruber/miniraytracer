#pragma once

#include <algorithm>
#include <vector>

// statically linked utility library

namespace utils {
	template <typename T>
	T clamp(T val, T lower, T upper) {
		return std::min(upper, std::max(val, lower));
	}

	auto solveQuadraticEquation(double a, double b, double c) -> std::vector<double>;
}
