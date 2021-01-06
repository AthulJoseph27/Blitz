#pragma once

#include <bits/stdc++.h>
#include <iostream>

double relu(double x)
{
    if (x > 0)
        return x;

    return 0.0;
}

double sigmoid(double x)
{
    return ((double)1) / (1 + exp(-x));
}

double tanh(double x)
{
    double a = exp(x);
    double b = exp(-x);

    return (a - b) / (a + b);
}

double softmax(double x, double sum)
{
    return exp(x) / sum;
}
