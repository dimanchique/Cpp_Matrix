#include "Matrix.h"

int main() {
    auto Mat = Matrix();
    Mat.SetData({{0, 1, 2}, {3, 4, 5}});
    Mat.PrintMatrix();
    auto mm = Mat.Copy();
    mm.T();
    return 0;
}
