#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>
#include <time.h>

class Matrix
{
private:
	int row, col;

public:
	std::vector<std::vector<double>> matrix;
	Matrix(int row, int col)
	{
		this->row = row;
		this->col = col;
		for (int i = 0; i < this->row; i++)
		{
			matrix.push_back({});
			for (int j = 0; j < this->col; j++)
			{
				matrix[i].push_back(0);
			}
		}
	}

	Matrix(std::vector<std::vector<double>> v)
	{

		for (int i = 0; i < v.size(); i++)
		{
			matrix.push_back({});
			for (int j = 0; j < v[0].size(); j++)
			{
				matrix[i].push_back(v[i][j]);
			}
		}
	}

	void scale(double value)
	{

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				matrix[i][j] *= value;
	}

	void add(double value)
	{

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				matrix[i][j] += value;
	}

	void transpose()
	{
		std::vector<std::vector<double>> result(matrix[0].size(), std::vector<double>(matrix.size()));

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				result[i][j] = matrix[j][i];

		matrix = result;
	}

	void multiply(Matrix B)
	{

		if (matrix[0].size() != B.matrix.size())
			throw std::invalid_argument("Matrices cannot be multiplied");

		// std::cout << "Hello" << std::endl;
		std::vector<std::vector<double>>
			product(matrix.size(), std::vector<double>(B.matrix[0].size(), 0));
		// Matrix mx = Matrix(product);
		// mx.print();
		for (int i = 0; i < product.size(); i++)
			for (int j = 0; j < product[0].size(); j++)
			{

				for (int k = 0; k < matrix[0].size(); k++)
					product[i][j] += (matrix[i][k] * B.matrix[k][j]);
			}

		matrix = product;
	}

	static std::vector<std::vector<double>> multiply(Matrix A, Matrix B)
	{
		if (A.matrix[0].size() != B.matrix.size())
			throw std::invalid_argument("Matrices cannot be multiplied");

		// std::cout << "Hello" << std::endl;
		std::vector<std::vector<double>>
			product(A.matrix.size(), std::vector<double>(B.matrix[0].size(), 0));
		// Matrix mx = Matrix(product);
		// mx.print();
		for (int i = 0; i < product.size(); i++)
			for (int j = 0; j < product[0].size(); j++)
			{

				for (int k = 0; k < A.matrix[0].size(); k++)
					product[i][j] += (A.matrix[i][k] * B.matrix[k][j]);
			}

		return product;
	}

	void preMultiply(Matrix B)
	{

		if (matrix[0].size() != B.matrix.size())
			throw std::invalid_argument("Matrices cannot be multiplied");

		std::vector<std::vector<double>> product(B.matrix.size(), std::vector<double>(matrix[0].size()));

		for (int i = 0; i < product.size(); i++)
			for (int j = 0; j < product[0].size(); j++)
			{

				for (int k = 0; k < matrix[0].size(); k++)
					product[i][j] += (matrix[k][i] * B.matrix[j][k]);
			}

		matrix = product;
	}

	void add(Matrix B)
	{

		if (B.matrix[0].size() != matrix[0].size() && matrix.size() != B.matrix.size())
			throw std::invalid_argument("Invalid Shape");

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				matrix[i][j] += B.matrix[i][j];
	}

	void substract(Matrix B)
	{

		if (B.matrix[0].size() != matrix[0].size() && matrix.size() != B.matrix.size())
			throw std::invalid_argument("Invalid Shape");

		B.scale(-1);
		add(B);
	}

	void randomize()
	{

		srand(time(NULL));

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				matrix[i][j] = (2.0f * (double)rand()) / ((double)RAND_MAX) - 1.0f;
	}

	void reshape(int row, int col)
	{
		if ((row * col) != (matrix[0].size() * matrix.size()))
			throw std::invalid_argument("Invalid shape");

		std::vector<std::vector<double>> newMatrix(row, std::vector<double>(col));

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				newMatrix[i][j] = matrix[(i * col + j) / matrix.size()][(i * col + j) % matrix.size()];

		matrix = newMatrix;
	}

	void map(double (*func)(double))
	{

		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[0].size(); j++)
				matrix[i][j] = (*func)(matrix[i][j]);
	}

	static double expSum(Matrix A)
	{
		double s = 0.0;

		for (int i = 0; i < A.matrix.size(); i++)
			s += exp(A.matrix[i][0]);

		return s;
	}

	static std::vector<double> oneDArray(Matrix A)
	{

		std::vector<double> result = {};

		for (auto i : A.matrix)
			result.push_back(i[0]);

		return result;
	}

	void print()
	{

		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[0].size(); j++)
				printf("%.6lf\t", matrix[i][j]);
			std::cout << "\n";
		}

		std::cout << '\n';
	}

	// double subDeterminant(std::vector<vector<double>> mat){

	// 	float D = 0;

	// 	if(matrix.size() == 0 || matrix[0].size() == 0)
	// 		throw std::invalid_argument("Cannot find determinant");

	// 	if(matrix.size() == 1 && matrix[0].size() == 1)
	// 		return matrix[0][0];

	// 	std::vector<std::vector<double>> temp;

	// 	int sign = 1;

	// 	for(int f=0;f<)

	// }

	// double determinant(){
	// 	return subDeterminant(matrix);
	// }
};
