#include "Matrix.h"

int main() {
    auto M = Matrix<float>({{1, 2, 3, 4}});
    auto S = 3 * M / 2;
    return 0;
}
