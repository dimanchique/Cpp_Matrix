#pragma once
#include "vector"

#define DEBUG

class Matrix {
private:
    int rows;
    int columns;
    std::vector<std::vector<float>> matrix;

public:
    Matrix();
    Matrix(int num_rows, int num_columns);
    ~Matrix();

private:
    void AllocMatrixData(int num_rows, int num_columns);
    void DeallocMatrixData();

public:
    void SetData(std::vector<std::vector<float>> Data);
    [[nodiscard]] std::vector<std::vector<float>> GetData() const { return matrix; }
    [[nodiscard]] Matrix Copy() const;
    static Matrix T(Matrix matrix);
    void T();
    static Matrix Inverse(Matrix matrix);
    void Inverse();

    static Matrix TrimMatrixRow(Matrix matrix, int row);
    void TrimMatrixRow(int row);
    static Matrix TrimMatrixColumn(Matrix matrix, int column);
    void TrimMatrixColumn(int column);
    static Matrix TrimMatrix(Matrix matrix, int row, int column);
    void TrimMatrix(int row, int column);
    static Matrix Reshape(Matrix matrix, int num_rows, int num_columns);
    void Reshape(int num_rows, int num_columns);

    void PrintMatrix();
    [[nodiscard]] int GetNumOfRows() const { return rows; }
    [[nodiscard]] int GetNumOfColumns() const { return columns; }
    [[nodiscard]] float Determinant() const;

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);
    Matrix &operator/=(const Matrix &other);

    bool operator==(const Matrix &other) const;

    Matrix operator+(float Value) const;
    Matrix operator-(float Value) const;
    Matrix operator*(float Value) const;
    Matrix operator/(float Value) const;
    Matrix &operator+=(float Value);
    Matrix &operator-=(float Value);
    Matrix &operator*=(float Value);
    Matrix &operator/=(float Value);
};
