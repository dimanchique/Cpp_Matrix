#include "Matrix.h"

int main() {
    auto Mat = Matrix(3,3);
    Mat.SetData({{5, -1, -1},
                 {1, 2, 3},
                 {4, 3, 2}});
    std::vector<float> solution = {0, 14, 16};
    std::vector<float> out;
    Mat.Solve(solution, out);
    return 0;
}
