#include "Matrix.h"

int main() {
    auto Mat = Matrix(3,3);
    Mat.SetData({{1, 0, 0},
                 {0, 1, 2},
                 {0, 0, 1}});
    const auto b1 = Mat.IsIdentityMatrix();
    const auto b2 = Mat.IsUpperTriangleMatrix();
    const auto b3 = Mat.IsLowerTriangleMatrix();
    const auto b4 = Mat.IsDiagonalMatrix();
    return 0;
}
