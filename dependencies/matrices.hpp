#include <iostream>
#include <stdexcept>

//1x1 Matrix
struct Matrix1x1 {
	// Element of the matrix
	float a;

	// Matrix Constructor
	Matrix1x1(float a_)
		: a(a_) {}

	Matrix1x1() : a(1) {}

	Matrix1x1 operator+(const Matrix1x1& other) const {
		return { a + other.a };
	}

	Matrix1x1 operator-(const Matrix1x1& other) const {
		return { a - other.a };
	}

	Matrix1x1 operator*(const Matrix1x1& other) const {
		return { a * other.a };
	}

	float determinant() const {
		return a;
	}

	Matrix1x1 inverse() const {
		float det = determinant();
		if(det == 0){
			throw std::runtime_error("Matrix is inversible");
		}
		float invDet = 1.0f/det;
		return { invDet };
	}

	void print() const {
        std::cout << "[" << a << "]" << std::endl;
    }
}; 

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

struct Matrix3x3 {
    float m[3][3];

    // Constructors
    Matrix3x3(float elems[3][3]) {
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                m[i][j] = elems[i][j];
    }

    Matrix3x3() { // Identity
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }

    // Addition
    Matrix3x3 operator+(const Matrix3x3& other) const {
        Matrix3x3 result;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    // Subtraction
    Matrix3x3 operator-(const Matrix3x3& other) const {
        Matrix3x3 result;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

    // Multiplication
    Matrix3x3 operator*(const Matrix3x3& other) const {
        Matrix3x3 result{};
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                result.m[i][j] = 0;
                for(int k=0;k<3;k++)
                    result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
        return result;
    }

    // Determinant
    float determinant() const {
        return 
            m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1]) -
            m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0]) +
            m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
    }

    // Inverse
    Matrix3x3 inverse() const {
        float det = determinant();
        if(det == 0) throw std::runtime_error("Matrix is not invertible");
        Matrix3x3 inv{};
        inv.m[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1])/det;
        inv.m[0][1] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1])/det;
        inv.m[0][2] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1])/det;

        inv.m[1][0] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0])/det;
        inv.m[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0])/det;
        inv.m[1][2] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0])/det;

        inv.m[2][0] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0])/det;
        inv.m[2][1] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0])/det;
        inv.m[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0])/det;

        return inv;
    }

    // Print
    void print() const {
        for(int i=0;i<3;i++){
            std::cout << "[ ";
            for(int j=0;j<3;j++)
                std::cout << m[i][j] << " ";
            std::cout << "]\n";
        }
    }
};
