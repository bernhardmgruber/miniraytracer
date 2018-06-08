#include "utils.h"

#include <cmath>

namespace utils {
	auto solveQuadraticEquation(double a, double b, double c) -> std::vector<double> {
		const double discriminat = std::pow(b, 2) - 4 * a * c;
		if (discriminat < 0)
			return {};

		if (discriminat == 0)
			return { -b / 2 * a };

		const auto x1 = (-b - std::sqrt(discriminat)) / 2 * a;
		const auto x2 = (-b + std::sqrt(discriminat)) / 2 * a;
		return { x1, x2 };
	}
}
