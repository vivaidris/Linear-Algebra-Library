#include <iostream>
#include <stdexcept>
#include <array>

//1x1 Matrix
struct Matrix1x1 {
	// Element of the matrix
	float a;

	// Matrix Constructor
	Matrix1x1(float a_)
		: a(a_) {}

	Matrix1x1() : a(1) {}

	//Addition Operator
	Matrix1x1 operator+(const Matrix1x1& other) const {
		return { a + other.a };
	}

	//Subtraction Operator
	Matrix1x1 operator-(const Matrix1x1& other) const {
		return { a - other.a };
	}

	//Product Operator
	Matrix1x1 operator*(const Matrix1x1& other) const {
		return { a * other.a };
	}

	//Determinant
	float determinant() const {
		return a;
	}

	//Inverse
	Matrix1x1 inverse() const {
		float det = determinant();
		if(det == 0){
			throw std::runtime_error("Matrix is inversible");
		}
		float invDet = 1.0f/det;
		return { invDet };
	}

	//Print (DEBUG ONLY)
	void print() const {
        std::cout << "[" << a << "]" << std::endl;
    }
}; 

//2x2 Matrix
struct Matrix2x2 {
	//Elements
	float m[2][2];

	//Constructors
	Matrix2x2(float elems[2][2]){
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				m[i][j] = elems[i][j];
			}
		}
	}

	Matrix2x2() {
		m[0][0] = 1; m[0][1] = 0;
		m[1][0] = 0; m[1][1] = 1;
	}

	//Float Support (DO NOT REMOVE)
	Matrix2x2(float a, float b, float c, float d) {
        m[0][0] = a; m[0][1] = b;
        m[1][0] = c; m[1][1] = d;
    }

	//Addition / Subtraction / Product Operators
	Matrix2x2 operator+(const Matrix2x2& other) const {
		Matrix2x2 result;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				result.m[i][j] = m[i][j] + other.m[i][j];
		return result;
	}	

	Matrix2x2 operator-(const Matrix2x2& other) const {
		Matrix2x2 result;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				result.m[i][j] = m[i][j] - other.m[i][j];
		return result;
	}

	Matrix2x2 operator*(const Matrix2x2& other) const {
		Matrix2x2 result{};
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++) {
				result.m[i][j] = 0;
				for(int k=0;k<2;k++)
					result.m[i][j] += m[i][k] * other.m[k][j];
			}
		return result;
	}

	// Determinant and Inverse
	float determinant() const {
		return m[0][0]*m[1][1] - m[0][1]*m[1][0];
	}

	Matrix2x2 inverse() const {
		float det = determinant();
		if(det == 0) throw std::runtime_error("Matrix not invertible");
		return Matrix2x2{ 
			m[1][1]/det,
			-m[0][1]/det,
        	-m[1][0]/det,
			m[0][0]/det
		};

	}

	//Print (DEBUG ONLY)
	void print() const {
        for(int i=0;i<2;i++){
            std::cout << "[ ";
            for(int j=0;j<2;j++)
                std::cout << m[i][j] << " ";
            std::cout << "]\n";
        }
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

    Matrix3x3() {
        m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
        m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
        m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
    }

    // Addition / Subtraction / Product Operators
    Matrix3x3 operator+(const Matrix3x3& other) const {
        Matrix3x3 result;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    Matrix3x3 operator-(const Matrix3x3& other) const {
        Matrix3x3 result;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

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

    // Determinant and Inverse
    float determinant() const {
        return 
            m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1]) -
            m[0][1]*(m[1][0]*m[2][2]-m[1][2]*m[2][0]) +
            m[0][2]*(m[1][0]*m[2][1]-m[1][1]*m[2][0]);
    }

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

    // Print (DEBUG ONLY)
    void print() const {
        for(int i=0;i<3;i++){
            std::cout << "[ ";
            for(int j=0;j<3;j++)
                std::cout << m[i][j] << " ";
            std::cout << "]\n";
        }
    }
};
