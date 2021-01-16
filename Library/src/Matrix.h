#pragma once

#include <vector>

class Matrix
{
private:
    int row, col;

public:
    std::vector<std::vector<double>> matrix;
    Matrix(int row, int col);
    Matrix(std::vector<std::vector<double>> v);
    void randomize();
    void reshape(int row, int col);
    void map(double (*func)(double));
    static double expSum(Matrix A);
    void scale(double value);
    void add(double value);
    void add(Matrix B);
    void substract(Matrix B);
    double sum();
    void transpose();
    void multiply(Matrix B);
    void hadamadProduct(Matrix B);
    static std::vector<std::vector<double>> multiply(Matrix A, Matrix B);
    void preMultiply(Matrix B);
    static std::vector<double> oneDArray(Matrix A);
    void print();
};
