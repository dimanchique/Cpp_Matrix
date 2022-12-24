#include "Matrix.h"

int main() {
    auto M = Matrix<float>({{1, 2, 3, 4}});
    auto M1 = Matrix<float>({
                                    std::vector<float>{1},
                                    std::vector<float>{2},
                                    std::vector<float>{3},
                                    std::vector<float>{4}
    });
    auto S = M1*M;
    auto S1 = M.MultiplyMixed(M1);
    auto d = 5*S*5*S;
    return 0;
}
