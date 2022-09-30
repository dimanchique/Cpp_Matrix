#include "Matrix.h"

int main() {
    auto Mat = Matrix();
    Mat.SetData({{2, 1, 1},
                 {1, -1, 0},
                 {3, -1, 2}});
    Mat.PrintMatrix();
    std::vector<float> roots;
    std::vector<float> solutions {2, -2, 2};
    Mat.Solve(solutions, roots);
    return 0;
}
