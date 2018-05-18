#pragma once

#include <array>
#include <cmath>
#include <stdexcept>
#include <iosfwd>

namespace math {
	template <typename F>
	class Vector {
	public:
		Vector() = default;
		Vector(F x, F y, F z)
			: values{{x, y, z}} {}

		Vector(const Vector&) = default;
		auto operator=(const Vector&) -> Vector& = default;

		// we do not need moves on this class, but why prevent them?
		Vector(Vector&&) noexcept = default;
		auto operator=(Vector&&) noexcept -> Vector& = default;

		auto operator[](std::size_t index) -> F& {
			return values[index];
		}

		auto operator[](std::size_t index) const -> F {
			return values[index];
		}

		auto operator+=(const Vector& v) noexcept -> Vector& {
			for (int i = 0; i < 3; i++)
				values[i] += v.values[i];
			return *this;
		}

		auto operator-=(const Vector& v) noexcept -> Vector& {
			for (int i = 0; i < 3; i++)
				values[i] -= v.values[i];
			return *this;
		}

		template <typename Scalar>
		auto operator*=(Scalar scalar) noexcept -> Vector& {
			for (int i = 0; i < 3; i++)
				values[i] *= scalar;
			return *this;
		}

		auto length() const noexcept {
			return std::sqrt((*this) * (*this));
		}

		void normalize() {
			const auto l = length();
			for (int i = 0; i < 3; i++)
				values[i] /= l;
		}

		auto normalized() const -> Vector {
			auto r = *this;
			r.normalize();
			return r;
		}

	private:
		std::array<F, 3> values = {{0, 0, 0}};
	};

	template <typename F>
	auto operator+(const Vector<F>& a, const Vector<F>& b) noexcept -> Vector<F> {
		auto r = a;
		r += b;
		return r;
	}

	template <typename F>
	auto operator-(const Vector<F>& a, const Vector<F>& b) noexcept -> Vector<F> {
		auto r = a;
		r -= b;
		return r;
	}

	template <typename F, typename Scalar>
	auto operator*(const Vector<F>& v, Scalar scalar) noexcept -> Vector<F> {
		auto r = v;
		r *= scalar;
		return r;
	}

	template <typename Scalar, typename F>
	auto operator*(Scalar scalar, const Vector<F>& v) noexcept -> Vector<F> {
		return v * scalar;
	}

	// dot product
	template <typename F>
	auto operator*(const Vector<F>& a, const Vector<F>& b) noexcept -> F {
		F r = 0;
		for (int i = 0; i < 3; i++)
			r += a[i] * b[i];
		return r;
	}

	// cross product
	template <typename F>
	auto operator%(const Vector<F>& a, const Vector<F>& b) -> Vector<F> {
		Vector<F> r;
		r[0] = a[1] * b[2] - a[2] * b[1];
		r[1] = a[2] * b[0] - a[0] * b[2];
		r[2] = a[0] * b[1] - a[1] * b[0];
		return r;
	}

	template <typename F>
	auto operator>>(std::istream& is, Vector<F>& v) -> std::istream& {
		for (int i = 0; i < 3; i++)
			is >> v[i];
		return is;
	}
		
	using VectorF = Vector<float>;
	using VectorD = Vector<double>;
}
