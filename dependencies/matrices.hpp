#include <iostream>
#include <stdexcept>

//2x2 Matrix
struct Matrix2x2 {
	// Elements of the matrix
	float a, b, c, d;

	// Matrix Constructor
	Matrix2x2(float a_, float b_, float c_, float d_)
		: a(a_), b(b_), c(c_), d(d_) {}

	Matrix2x2() : a(1), b(0), c(0), d(1) {}

	// Matrix Addition
	Matrix2x2 operator+(const Matrix2x2& other) const {
		return { a + other.a, b + other.b, c + other.c , d + other.d };
	}

	// Matrix Subtraction
	Matrix2x2 operator-(const Matrix2x2& other) const {
		return { a - other.a, b - other.b, c - other.c, d - other.d };
	}

	// Matrix Multiplication
	Matrix2x2 operator*(const Matrix2x2& other) const {
		return {
			a * other.a + b * other.c,
			a * other.b + b * other.d,
			c * other.a + d * other.c,
			c * other.b + d * other.d
		};
	}

	// Matrix-Vector Multiplication
	std::pair<float, float> operator*(const std::pair<float, float>& vec) const {
		return {
			a * vec.first + b * vec.second,
			c * vec.first + d * vec.second
		};
	}

	// Determinant
	float determinant() const {
		return a * d - b * c;
	}

	// Inverse
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

	// Transpose
	Matrix2x2 transpose() const {
		return { a, c, b, d };
	}

	// Print (DEBUGGING PURPOSES)
	void print() const {
		std::cout << "[" << a << "," << b << "]" << std::endl
			      << "[" << c << "," << d << "]" << std::endl;
	}
};
