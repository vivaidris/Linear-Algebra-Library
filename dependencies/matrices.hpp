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

struct Matrix4x4 {
    float m[4][4];

    // Constructor from 2D array
    Matrix4x4(float elems[4][4]) {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                m[i][j] = elems[i][j];
    }

    // Default constructor (identity)
    Matrix4x4() {
        for(int i = 0;i<4;i++)
            for(int j = 0;j<4;j++)
                m[i][j] = (i==j) ? 1.0f : 0.0f;
    }

    // Optional: 16-float constructor
    Matrix4x4(float a00,float a01,float a02,float a03,
              float a10,float a11,float a12,float a13,
              float a20,float a21,float a22,float a23,
              float a30,float a31,float a32,float a33) 
    {
        m[0][0]=a00; m[0][1]=a01; m[0][2]=a02; m[0][3]=a03;
        m[1][0]=a10; m[1][1]=a11; m[1][2]=a12; m[1][3]=a13;
        m[2][0]=a20; m[2][1]=a21; m[2][2]=a22; m[2][3]=a23;
        m[3][0]=a30; m[3][1]=a31; m[3][2]=a32; m[3][3]=a33;
    }

    // Addition
    Matrix4x4 operator+(const Matrix4x4& other) const {
        Matrix4x4 result;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                result.m[i][j] = m[i][j] + other.m[i][j];
        return result;
    }

    // Subtraction
    Matrix4x4 operator-(const Matrix4x4& other) const {
        Matrix4x4 result;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                result.m[i][j] = m[i][j] - other.m[i][j];
        return result;
    }

    // Multiplication
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result{};
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++) {
                result.m[i][j] = 0;
                for(int k=0;k<4;k++)
                    result.m[i][j] += m[i][k]*other.m[k][j];
            }
        return result;
    }

    // Minor determinant helper (3x3)
    float minor(int r0,int r1,int r2,int c0,int c1,int c2) const {
        return m[r0][c0]*(m[r1][c1]*m[r2][c2]-m[r1][c2]*m[r2][c1])
             - m[r0][c1]*(m[r1][c0]*m[r2][c2]-m[r1][c2]*m[r2][c0])
             + m[r0][c2]*(m[r1][c0]*m[r2][c1]-m[r1][c1]*m[r2][c0]);
    }

    // Determinant
    float determinant() const {
        return m[0][0]*minor(1,2,3,1,2,3)
             - m[0][1]*minor(1,2,3,0,2,3)
             + m[0][2]*minor(1,2,3,0,1,3)
             - m[0][3]*minor(1,2,3,0,1,2);
    }

    // Inverse
    Matrix4x4 inverse() const {
        float det = determinant();
        if(det==0) throw std::runtime_error("Matrix not invertible");

        Matrix4x4 inv;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                // Compute minor for element (j,i) and apply checkerboard sign
                int rows[3], cols[3], r=0, c=0;
                for(int ri=0; ri<4; ri++) if(ri!=i) rows[r++] = ri;
                for(int ci=0; ci<4; ci++) if(ci!=j) cols[c++] = ci;
                float cofactor = minor(rows[0],rows[1],rows[2],cols[0],cols[1],cols[2]);
                inv.m[j][i] = ((i+j)%2==0 ? 1:-1)*cofactor/det; // note transpose
            }
        }
        return inv;
    }

    // Print
    void print() const {
        for(int i=0;i<4;i++){
            std::cout << "[ ";
            for(int j=0;j<4;j++)
                std::cout << m[i][j] << " ";
            std::cout << "]\n";
        }
    }
};
