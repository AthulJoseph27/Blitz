#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "Matrix.h"
#include "NeuralNetwork.h"

double tf(double v)
{
	return sin(v);
}

int main()
{
	// Matrix a = Matrix({{0},
	// 				   {0},
	// 				   {0}});

	// Matrix b = Matrix({{7, 8},
	// 				   {9, 10},
	// 				   {11, 12}});

	// a.multiply(b);
	// a.print();
	NeuralNetwork nn = NeuralNetwork({3, 3, 2}, {"sigmoid", "softmax"});
	nn.print();
	nn.feedForward({1, 2, 3});
	nn.print();
	// return 0;
}