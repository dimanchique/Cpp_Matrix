#include <cstdio>
#include <cmath>
#include "Matrix.h"

Matrix::Matrix() {
#ifdef DEBUG
   std::cout << "Empty matrix was created. ADDR: " << this << "\n";
#endif
}

Matrix::Matrix(const std::vector<std::vector<float>> &Data) {
#ifdef DEBUG
    auto t = Timer("Matrix::Matrix(const std::vector<std::vector<float>> &Data)");
#endif
    SetData(Data);
}

Matrix::Matrix(const std::vector<ProxyVector> &Data) {
#ifdef DEBUG
    auto t = Timer("Matrix::Matrix(const std::vector<ProxyVector> &Data)");
#endif
    SetData(Data);
}

Matrix::Matrix(int num_rows, int num_columns) {
#ifdef DEBUG
    auto t = Timer("Matrix::Matrix(int num_rows, int num_columns)");
#endif
    AllocMatrixData(num_rows, num_columns);
#ifdef DEBUG
    std::cout << "Matrix was created. ADDR: " << this << "\n";
    std::cout << "Reserved space: " << rows << " rows, " << columns << " columns\n";
#endif
}

Matrix::~Matrix() {
#ifdef DEBUG
    auto t = Timer("Matrix::~Matrix()");
#endif
    DeallocMatrixData();
#ifdef DEBUG
    std::cout << "Matrix was deleted. ADDR: " << this << "\n";
#endif
}

Matrix Matrix::Copy() const {
#ifdef DEBUG
    auto t = Timer("Matrix::Copy()");
#endif
    auto temp = Matrix(*this);
#ifdef DEBUG
    std::cout << "Copied matrix from " << this << " to " << &temp << "\n";
#endif
    return temp;
}

void Matrix::AllocMatrixData(int num_rows, int num_columns) {
#ifdef DEBUG
    auto t = Timer("Matrix::AllocMatrixData(int num_rows, int num_columns)");
#endif
    DeallocMatrixData();
    rows = num_rows;
    columns = num_columns;
    for (int i = 0; i < rows; i++)
        matrix.emplace_back(columns);
#ifdef DEBUG
    std::cout << "Memory for matrix data was allocated. ADDR: " << &matrix << "\n";
#endif
}

void Matrix::DeallocMatrixData() {
#ifdef DEBUG
    auto t = Timer("Matrix::DeallocMatrixData()");
#endif
    matrix.clear();
    rows = 0;
    columns = 0;
#ifdef DEBUG
    std::cout << "Memory for matrix was deallocated. ADDR: " << &matrix << "\n";
#endif
}

void Matrix::SetRow(const std::vector<float> &Data, int n) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetRow(const std::vector<float> &Data, int n)");
#endif
    assert(n < rows);
    matrix[n] = Data;
}

void Matrix::SetRow(const ProxyVector &Data, int n) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetRow(const ProxyVector &Data, int n)");
#endif
    assert(n < rows);
    matrix[n] = Data;
}

void Matrix::SetColumn(const std::vector<float> &Data, int n) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetColumn(const std::vector<float> &Data, int n)");
#endif
    assert(n < columns);
    for(int i = 0; i < columns; i++){
        matrix[i][n] = Data[i];
    }
}

void Matrix::SetColumn(const ProxyVector &Data, int n) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetColumn(const ProxyVector &Data, int n)");
#endif
    assert(n < columns);
    for(int i = 0; i < columns; i++){
        matrix[i][n] = Data[i];
    }
}

void Matrix::SetData(const std::vector<std::vector<float>> &Data) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetData(const std::vector<std::vector<float>> &Data)");
#endif
    DeallocMatrixData();
    for (int i = 0; i < Data.size(); i++) {
        matrix.emplace_back();
        matrix[i] = Data[i];
        columns = Data[i].size();
        rows++;
    }
#ifdef DEBUG
    std::cout << "Matrix data was loaded: " << rows << " rows, " << columns << " columns\n";
#endif
}

void Matrix::SetData(const std::vector<ProxyVector> &Data) {
#ifdef DEBUG
    auto t = Timer("Matrix::SetData(const std::vector<ProxyVector> &Data)");
#endif
    DeallocMatrixData();
    for (int i = 0; i < Data.size(); i++) {
        matrix.emplace_back();
        matrix[i] = Data[i];
        columns = Data[i].size();
        rows++;
    }
#ifdef DEBUG
    std::cout << "Matrix data was loaded: " << rows << " rows, " << columns << " columns\n";
#endif
}

void Matrix::T() {
#ifdef DEBUG
    auto t = Timer("Matrix::T()");
#endif
    auto temp = Copy();
    AllocMatrixData(temp.columns, temp.rows);
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            matrix[j][i] = temp.matrix[i][j];
}

void Matrix::Inverse() {
#ifdef DEBUG
    auto t = Timer("Matrix::Inverse()");
#endif
    float det = Determinant();
    if (fabsf(det) < 0.00005f) //epsilon
    {
#ifdef DEBUG
        printf("Can't inverse matrix with D = 0\n");
#endif
        return;
    }

    auto minor_m = Copy();
    auto origin = Copy();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            auto temp = Matrix::TrimMatrix(origin, i, j);
            minor_m.matrix[i][j] = temp.Determinant();
        }

    float sign = 1;
    for (int i = 0; i < minor_m.rows; i++)
        for (int j = 0; j < minor_m.columns; j++) {
            minor_m.matrix[i][j] *= sign;
            sign *= -1;
        }

    minor_m.T();
    minor_m /= det;
    matrix = minor_m.matrix;
}

void Matrix::TrimMatrixRow(int row) {
#ifdef DEBUG
    auto t = Timer("Matrix::TrimMatrixRow(int row)");
#endif
    if (row >= matrix.size()) {
        printf("Row %d doesn't exist\n", row);
        return;
    }
    matrix.erase(matrix.begin() + row);
    rows--;
}

void Matrix::TrimMatrixColumn(int column) {
#ifdef DEBUG
    auto t = Timer("Matrix::TrimMatrixColumn(int column)");
#endif
    for (auto &row: matrix) {
        if (column >= row.size()) {
            printf("Column %d doesn't exist\n", column);
            return;
        }
        row.erase(column);
    }
    columns--;
}

void Matrix::TrimMatrix(int row, int column) {
#ifdef DEBUG
    auto t = Timer("Matrix::TrimMatrix(int row, int column)");
#endif
    TrimMatrixRow(row);
    TrimMatrixColumn(column);
}

void Matrix::Reshape(int num_rows, int num_columns) {
#ifdef DEBUG
    auto t = Timer("Matrix::Reshape(int num_rows, int num_columns)");
#endif
    assert(rows * columns == num_rows * num_columns);
    Matrix temp = Copy();
    AllocMatrixData(num_rows, num_columns);
    int CurrentRow = 0;
    int CurrentColumn = 0;
    for (int i = 0; i < temp.rows; i++) {
        for (int j = 0; j < temp.columns; j++) {
            matrix[CurrentRow][CurrentColumn] = temp.matrix[i][j];
            CurrentColumn++;
            if (CurrentColumn == num_columns) {
                CurrentColumn = 0;
                CurrentRow++;
            }
        }
    }
}

void Matrix::ReplaceRow(const int num_row, const std::vector<float> &new_row) {
#ifdef DEBUG
    auto t = Timer("Matrix::ReplaceRow(const int num_row, const std::vector<float> &new_row)");
#endif
    assert(new_row.size() == columns);
    assert(num_row <= rows);
    matrix[num_row] = new_row;
}

void Matrix::ReplaceColumn(int num_column, std::vector<float> &new_column) {
#ifdef DEBUG
    auto t = Timer("Matrix::ReplaceColumn(int num_column, std::vector<float> &new_column)");
#endif
    assert(new_column.size() == rows);
    assert(num_column <= columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (j == num_column)
                matrix[i][j] = new_column[i];
}

bool Matrix::IsDiagonalMatrix() const {
#ifdef DEBUG
    auto t = Timer("Matrix::IsDiagonalMatrix()");
#endif
    if (rows != columns)
    {
#ifdef DEBUG
        printf("IsDiagonalMatrix function is not defined for non-square matrix\n");
#endif
        return false;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if ((i == j && matrix[i][j] == 0) || (i != j && matrix[i][j] != 0))
                return false;
        }
    return true;
}

bool Matrix::IsUpperTriangleMatrix() const {
#ifdef DEBUG
    auto t = Timer("Matrix::IsUpperTriangleMatrix()");
#endif
    if (rows != columns)
    {
#ifdef DEBUG
        printf("IsUpperTriangleMatrix function is not defined for non-square matrix\n");
#endif
        return false;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (i > j && matrix[i][j] != 0)
                return false;
        }
    return true;
}

bool Matrix::IsLowerTriangleMatrix() const {
#ifdef DEBUG
    auto t = Timer("Matrix::IsLowerTriangleMatrix()");
#endif
    if (rows != columns)
    {
#ifdef DEBUG
        printf("IsLowerTriangleMatrix function is not defined for non-square matrix\n");
#endif
        return false;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (i < j && matrix[i][j] != 0)
                return false;
        }
    return true;
}

bool Matrix::IsIdentityMatrix() const {
#ifdef DEBUG
    auto t = Timer("Matrix::IsIdentityMatrix()");
#endif
    if (rows != columns)
    {
#ifdef DEBUG
        printf("IsIdentityMatrix function is not defined for non-square matrix\n");
#endif
        return false;
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0))
                return false;
        }
    return true;
}

Matrix Matrix::T(Matrix matrix) {
    matrix.T();
    return matrix;
}

Matrix Matrix::Inverse(Matrix matrix) {
    matrix.Inverse();
    return matrix;
}

Matrix Matrix::TrimMatrixRow(Matrix matrix, int row) {
    matrix.TrimMatrixRow(row);
    return matrix;
}

Matrix Matrix::TrimMatrixColumn(Matrix matrix, int column) {
    matrix.TrimMatrixColumn(column);
    return matrix;
}

Matrix Matrix::TrimMatrix(Matrix matrix, int row, int column) {
    matrix.TrimMatrix(row, column);
    return matrix;
}

Matrix Matrix::Reshape(Matrix matrix, int num_rows, int num_columns) {
    matrix.Reshape(num_rows, num_columns);
    return matrix;
}

Matrix Matrix::ReplaceRow(Matrix matrix, int num_row, std::vector<float> &new_row) {
    matrix.ReplaceRow(num_row, new_row);
    return matrix;
}

Matrix Matrix::ReplaceColumn(Matrix matrix, int num_column, std::vector<float> &new_column) {
    matrix.ReplaceColumn(num_column, new_column);
    return matrix;
}

void Matrix::PrintMatrix() {
    printf("\nPrinting matrix. Rows: %d, Columns: %d\n", rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

float Matrix::Determinant() const {
#ifdef DEBUG
    auto t = Timer("Matrix::Determinant()");
#endif
    assert(rows == columns);
    if (rows == 1)
        return matrix[0][0];
    if (rows == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    float det = 0;
    int sign = 1;

    for (int f = 0; f < rows; f++) {
        auto temp = Copy();
        temp.TrimMatrix(0, f);
        det += sign * matrix[0][f] * temp.Determinant();
        sign = -sign;
    }
    return det;
}

bool Matrix::Solve(std::vector<float> &solution, std::vector<float> &out_roots) const {
#ifdef DEBUG
    auto t = Timer("Matrix::Solve(std::vector<float> &solution, std::vector<float> &out_roots)");
#endif
    assert(solution.size() == rows);
    float D = Determinant();
    std::vector<float> Ds{};

    if (D * D < 0.001) return false;

    out_roots.clear();
    for (int j = 0; j < columns; j++) {
        auto temp = Copy();
        temp.ReplaceColumn(j, solution);
        Ds.emplace_back(temp.Determinant());
    }
    for (auto &Det: Ds)
        out_roots.emplace_back(Det / D);

    return true;
}

Matrix Matrix::operator+(const Matrix &other) const {
    Matrix temp(*this);
    temp += other;
    return temp;
}

Matrix Matrix::operator-(const Matrix &other) const {
    Matrix temp(*this);
    temp -= other;
    return temp;
}

Matrix Matrix::operator*(const Matrix &other) const {
    Matrix temp(*this);
    temp *= other;
    return temp;
}

Matrix Matrix::operator/(const Matrix &other) const {
    Matrix temp(*this);
    temp /= other;
    return temp;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    assert(columns == other.columns && rows == other.rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] += other.matrix[i][j];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    assert(columns == other.columns && rows == other.rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] -= other.matrix[i][j];
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    Matrix temp = Matrix(rows, other.columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.rows; j++) {
            temp.matrix[i][j] = 0;
            for (int k = 0; k < columns; k++)
                temp.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
    AllocMatrixData(temp.rows, temp.columns);
    matrix = temp.matrix;
    return *this;
}

Matrix &Matrix::operator/=(const Matrix &other) {
    Matrix temp = other.Copy();
    temp.Inverse();
    Matrix origin(*this);
    origin *= temp;
    return *this;
}

Matrix Matrix::operator+(float Value) const {
    Matrix temp(*this);
    temp += Value;
    return temp;
}

Matrix Matrix::operator-(float Value) const {
    Matrix temp(*this);
    temp -= Value;
    return temp;
}

Matrix Matrix::operator*(float Value) const {
    Matrix temp(*this);
    temp *= Value;
    return temp;
}

Matrix Matrix::operator/(float Value) const {
    Matrix temp(*this);
    temp /= Value;
    return temp;
}

Matrix &Matrix::operator+=(float Value) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] += Value;
    return *this;
}

Matrix &Matrix::operator-=(float Value) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] -= Value;
    return *this;
}

Matrix &Matrix::operator*=(float Value) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] *= Value;
    return *this;
}

Matrix &Matrix::operator/=(float Value) {
    assert(Value != 0.0f);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            matrix[i][j] /= Value;
    return *this;
}

bool Matrix::operator==(Matrix &other) const {
    bool SizeEquality = columns == other.columns && rows == other.rows;
    bool ValuesEquality = true;
    for (int i = 0; i < rows; i++)
        if (matrix[i] != other.matrix[i]) {
            ValuesEquality = false;
            break;
        }
    return SizeEquality && ValuesEquality;
}

ProxyVector &Matrix::operator[](const int idx) {
    assert(idx < matrix.size());
    return matrix.at(idx);
}

ProxyVector Matrix::operator[](const int idx) const {
    assert(idx < matrix.size());
    return matrix.at(idx);
}
