#include "dependencies/matrices.hpp"

int main() {
    Matrix2x2 m1(1, 2, 3, 4);
    Matrix2x2 m2(5, 6, 7, 8);

    auto sum = m1 + m2;
    auto diff = m1 - m2;
    auto prod = m1 * m2;
    auto det = m1.determinant();
    auto trans = m1.transpose();

    sum.print();
    diff.print();
    prod.print();

    std::cout << "Determinant: " << det << "\n";

    auto inv = m1.inverse();
    inv.print();

    auto vec = std::make_pair(1.0f, 1.0f);
    auto resultVec = m1 * vec;
    std::cout << "Vector multiplication result: (" << resultVec.first << ", " << resultVec.second << ")\n";

    return 0;
}
