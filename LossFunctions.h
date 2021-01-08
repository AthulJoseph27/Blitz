#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include "Matrix.h"
#include <stdexcept>

Matrix MSE(std::vector<double> YA, std::vector<double> YO)
{
    if ((YA.size() != YO.size()))
        std::invalid_argument("Loss Function MSE, invalid vector sizes");

    Matrix error = Matrix(YA.size(), 1);

    for (int i = 0; i < error.matrix.size(); i++)
        error.matrix[i][0] = (YA[i] - YO[i]);

    return error;
}