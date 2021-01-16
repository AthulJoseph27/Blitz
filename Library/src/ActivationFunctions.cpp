#include "ActivationFunctions.h"
#include <math.h>
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

// double Tanh(double x)
// {
//     double a = exp(x);
//     double b = exp(-x);

//     return (a - b) / (a + b);
// }

double softmax(double x, double sum)
{
    return exp(x) / sum;
}

double derivativeRelu(double x)
{
    if (x > 0)
        return 1.0;
    return 0.0;
}

double derivativeTanh(double y)
{
    return (1 - pow(y, 2));
}

double derivativeSigmoid(double y)
{
    return y * (1 - y);
}
// namespace activation