#include <cstdio>
#include <cassert>
#include <cmath>
#include "Matrix.h"

Matrix::Matrix() {
    rows = 0;
    columns = 0;
#ifdef DEBUG
    printf("Empty matrix was created. ADDR: 0x%x\n", this);
#endif
}

Matrix::Matrix(int num_rows, int num_columns) {
    AllocMatrixData(num_rows, num_columns);

#ifdef DEBUG
    printf("Matrix was created. ADDR: 0x%x\n", this);
    printf("Reserved space: Rows: %d, Columns: %d\n", rows, columns);
#endif
}

void Matrix::AllocMatrixData(int num_rows, int num_columns) {
    DeallocMatrixData();
    rows = num_rows;
    columns = num_columns;
    for(int i = 0; i < rows; i++)
        matrix.emplace_back(std::vector<float>(columns));
#ifdef DEBUG
    printf("Memory for matrix data was allocated. ADDR: 0x%x\n", &matrix);
#endif
}

Matrix::~Matrix() {
    DeallocMatrixData();
#ifdef DEBUG
    printf("Matrix was deleted. ADDR: 0x%x\n", this);
#endif
}

void Matrix::DeallocMatrixData() {
    for(auto &i : matrix)
        i.clear();
    matrix.clear();
    rows = 0;
    columns = 0;
#ifdef DEBUG
    printf("Memory for matrix was deallocated. ADDR: 0x%x\n", &matrix);
#endif
}

void Matrix::SetData(std::vector<std::vector<float>> Data) {
    DeallocMatrixData();
    for(int i = 0; i < Data.size(); i++)
    {
        matrix.emplace_back();
        for(int j = 0; j < Data[i].size(); j++)
        {
            if (i==0)
                columns++;
            matrix[i].emplace_back(Data[i][j]);
        }
        rows++;
    }
#ifdef DEBUG
    printf("Matrix data was loaded. Rows: %d, Columns: %d\n", rows, columns);
#endif
}

Matrix Matrix::Copy() const {
    auto temp = Matrix(rows, columns);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
            temp.matrix[i][j] = matrix[i][j];
#ifdef DEBUG
    printf("Copied matrix from 0x%x to 0x%x\n", this, &temp);
#endif
    return temp;
}

Matrix Matrix::T(Matrix matrix) {
    auto temp = Matrix(matrix.columns, matrix.rows);
    for(int i = 0; i < matrix.rows; i++)
        for(int j = 0; j < matrix.columns; j++)
            temp.matrix[j][i] = matrix.matrix[i][j];
    return temp;
}

void Matrix::T() {
    auto temp = Copy();
    AllocMatrixData(temp.columns, temp.rows);
    for(int i = 0; i < columns; i++)
        for(int j = 0; j < rows; j++)
            matrix[j][i] = temp.matrix[i][j];
}

Matrix Matrix::Inverse(Matrix matrix) {
    matrix.Inverse();
    return matrix;
}

void Matrix::Inverse() {
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
    minor_m/=det;
    matrix = minor_m.matrix;
}

Matrix Matrix::TrimMatrixRow(Matrix matrix, int row) {
    matrix.TrimMatrixRow(row);
    return matrix;
}

void Matrix::TrimMatrixRow(int row) {
    if (row>=matrix.size())
    {
        printf("Row %d doesn't exist\n", row);
        return;
    }
    matrix.erase(matrix.begin() + row);
    rows--;
}

Matrix Matrix::TrimMatrixColumn(Matrix matrix, int column) {
    matrix.TrimMatrixColumn(column);
    return matrix;
}

void Matrix::TrimMatrixColumn(int column) {
    for (auto &row : matrix)
    {
        if (column>=row.size())
        {
            printf("Column %d doesn't exist\n", column);
            return;
        }
        row.erase(row.begin() + column);
    }
    columns--;
}

Matrix Matrix::TrimMatrix(Matrix matrix, int row, int column) {
    matrix.TrimMatrix(row, column);
    return matrix;
}

void Matrix::TrimMatrix(int row, int column) {
    TrimMatrixRow(row);
    TrimMatrixColumn(column);
}

Matrix Matrix::Reshape(Matrix matrix, int num_rows, int num_columns) {
    matrix.Reshape(num_rows, num_columns);
    return matrix;
}

void Matrix::Reshape(int num_rows, int num_columns) {
    assert(rows * columns == num_rows * num_columns);
    Matrix temp = Copy();
    AllocMatrixData(num_rows, num_columns);
    int CurrentRow = 0;
    int CurrentColumn = 0;
    for (int i = 0; i < temp.rows; i++) {
        for (int j = 0; j < temp.columns; j++) {
            matrix[CurrentRow][CurrentColumn] = temp.matrix[i][j];
            CurrentColumn++;
            if (CurrentColumn == num_columns)
            {
                CurrentColumn = 0;
                CurrentRow++;
            }
        }
    }
}

void Matrix::PrintMatrix() {
    printf("Printing matrix. Rows: %zu, Columns: %zu\n", matrix.size(), matrix[0].size());
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

float Matrix::Determinant() const {
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
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] += other.matrix[i][j];
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    assert(columns == other.columns && rows == other.rows);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] -= other.matrix[i][j];
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    Matrix temp = Matrix(rows, other.columns);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < other.rows; j++)
        {
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
    origin*=temp;
    return *this;
}

bool Matrix::operator==(const Matrix &other) const {
    bool size = columns == other.columns && rows == other.rows;
    bool values = true;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            if (matrix[i][j] != other.matrix[i][j])
            {
                values = false;
                break;
            }
    return size && values;
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
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] += Value;
    return *this;
}

Matrix &Matrix::operator-=(float Value) {
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] -= Value;
    return *this;
}

Matrix &Matrix::operator*=(float Value) {
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] *= Value;
    return *this;
}

Matrix &Matrix::operator/=(float Value) {
    assert(Value != 0.0f);
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < rows; j++)
            matrix[i][j] /= Value;
    return *this;
}
