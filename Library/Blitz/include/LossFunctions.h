#pragma once

#include "Matrix.h"

double max(double a, double b);
Matrix DifferenceError(std::vector<double> YA, std::vector<double> YO);
Matrix CrossEntropy(std::vector<double> YA, std::vector<double> YO);
Matrix Hinge(std::vector<double> YA, std::vector<double> YO);