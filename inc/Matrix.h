#pragma once

#include "ProxyVector.h"
#include "vector"
#include <cassert>

#define DEBUG

class Matrix {
private:
    int rows = 0;
    int columns = 0;
    std::vector<ProxyVector> matrix{};

public:
    Matrix();
    explicit Matrix(const std::vector<std::vector<float>> &Data);
    explicit Matrix(const std::vector<ProxyVector> &Data);
    Matrix(int num_rows, int num_columns);
    ~Matrix();

    [[nodiscard]] Matrix Copy() const;

private:
    void AllocMatrixData(int num_rows, int num_columns);
    void DeallocMatrixData();

public:
    void SetRow(const std::vector<float> &Data, int n);
    void SetRow(const ProxyVector &Data, int n);
    void SetColumn(const std::vector<float> &Data, int n);
    void SetColumn(const ProxyVector &Data, int n);
    [[nodiscard]] int GetRows() const { return rows; }
    [[nodiscard]] int GetColumns() const { return columns; }
    void SetData(const std::vector<std::vector<float>> &Data);
    void SetData(const std::vector<ProxyVector> &Data);
    [[nodiscard]] std::vector<ProxyVector> GetData() const { return matrix; }

    void T();
    void Inverse();
    void TrimMatrixRow(int row);
    void TrimMatrixColumn(int column);
    void TrimMatrix(int row, int column);
    void Reshape(int num_rows, int num_columns);
    void ReplaceRow(int num_row, const std::vector<float> &new_row);
    void ReplaceColumn(int num_column, std::vector<float> &new_column);

    [[nodiscard]] bool IsDiagonalMatrix() const;
    [[nodiscard]] bool IsUpperTriangleMatrix() const;
    [[nodiscard]] bool IsLowerTriangleMatrix() const;
    [[nodiscard]] bool IsIdentityMatrix() const;

    static Matrix T(Matrix matrix);
    static Matrix Inverse(Matrix matrix);
    static Matrix TrimMatrixRow(Matrix matrix, int row);
    static Matrix TrimMatrixColumn(Matrix matrix, int column);
    static Matrix TrimMatrix(Matrix matrix, int row, int column);
    static Matrix Reshape(Matrix matrix, int num_rows, int num_columns);
    static Matrix ReplaceRow(Matrix matrix, int num_row, std::vector<float> &new_row);
    static Matrix ReplaceColumn(Matrix matrix, int num_column, std::vector<float> &new_column);

    void PrintMatrix();
    [[nodiscard]] float Determinant() const;
    bool Solve(std::vector<float> &solution, std::vector<float> &out_roots) const;

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);
    Matrix &operator/=(const Matrix &other);

    Matrix operator+(float Value) const;
    Matrix operator-(float Value) const;
    Matrix operator*(float Value) const;
    Matrix operator/(float Value) const;
    Matrix &operator+=(float Value);
    Matrix &operator-=(float Value);
    Matrix &operator*=(float Value);
    Matrix &operator/=(float Value);
    bool operator==(Matrix &other) const;

    ProxyVector &operator[](int idx);
    ProxyVector operator[](int idx) const;
};
