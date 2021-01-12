#pragma once

#include <iostream>
#include "Matrix.h"
#include <stdexcept>

double max(double a, double b)
{
    if (a > b)
        return a;
    return b;
}

Matrix DifferenceError(std::vector<double> YA, std::vector<double> YO)
{
    if ((YA.size() != YO.size()))
        std::invalid_argument("Loss Function DifferenceError, invalid vector sizes");

    Matrix error = Matrix(YA.size(), 1);

    for (int i = 0; i < error.matrix.size(); i++)
        error.matrix[i][0] = (YA[i] - YO[i]);

    return error;
}

Matrix CrossEntropy(std::vector<double> YA, std::vector<double> YO)
{
    if ((YA.size() != YO.size()))
        std::invalid_argument("Loss Function DifferenceError, invalid vector sizes");

    Matrix error = Matrix(YA.size(), 1);

    for (int i = 0; i < error.matrix.size(); i++)
    {
        if (YA[i] == 1)
        {
            if (YO[i] == 0)
                error.matrix[i][0] = 1000;
            error.matrix[i][0] = -log(YO[i]);
        }
        else
            error.matrix[i][0] = -log(1 - YO[i]);
    }

    return error;
}

Matrix Hinge(std::vector<double> YA, std::vector<double> YO)
{
    if ((YA.size() != YO.size()))
        std::invalid_argument("Loss Function DifferenceError, invalid vector sizes");

    Matrix error = Matrix(YA.size(), 1);

    for (int i = 0; i < error.matrix.size(); i++)
    {
        error.matrix[i][0] = max(0, YA[i] - (1 - 2 * YA[i]) * YO[i]);
    }

    return error;
}