#include <iostream>
#include <stdexcept>

struct Matrix2x2 {
	float a, b, c, d;

	Matrix2x2(float a_, float b_, float c_, float d_)
		: a(a_), b(b_), c(c_), d(d_) {}

	Matrix2x2() : a(1), b(0), c(0), d(1) {}

	Matrix2x2 operator+(const Matrix2x2& other) const {
		return { a + other.a, b + other.b, c + other.c , d + other.d };
	}

	Matrix2x2 operator-(const Matrix2x2& other) const {
		return { a - other.a, b - other.b, c - other.c, d - other.d };
	}

	Matrix2x2 operator*(const Matrix2x2& other) const {
		return {
			a * other.a + b * other.c,
			a * other.b + b * other.d,
			c * other.a + d * other.c,
			c * other.b + d * other.d
		};
	}

	std::pair<float, float> operator*(const std::pair<float, float>& vec) const {
		return {
			a * vec.first + b * vec.second,
			c * vec.first + d * vec.second
		};
	}

	float determinant() const {
		return a * d - b * c;
	}

	Matrix2x2 inverse() const {
		float det = determinant();
		if (det == 0) {
			throw std::runtime_error("Matrix is not invertible");
		}
		float invDet = 1.0f / det;
		return {
			d * invDet,
			-b * invDet,
			-c * invDet,
			a * invDet
		};
	}

	Matrix2x2 transpose() const {
		return { a, c, b, d };
	}

	void print() const {
		std::cout << "[" << a << "," << b << "]" << std::endl
			      << "[" << c << "," << d << "]" << std::endl;
	}
};
