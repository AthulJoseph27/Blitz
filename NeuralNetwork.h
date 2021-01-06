#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>
#include <time.h>
#include "Matrix.h"
#include "ActivationFunctions.h"

class NeuralNetwork
{
private:
	std::vector<int> layerCount;
	std::vector<Matrix> layers;
	std::vector<Matrix> weights;
	std::vector<Matrix> bias;
	std::vector<std::string> activation;

public:
	NeuralNetwork(std::vector<int> layerCount, std::vector<std::string> activation)
	{
		this->activation = activation;
		this->layerCount = layerCount;
		layers.push_back(Matrix(this->layerCount[0], 1));
		for (int i = 1; i < this->layerCount.size(); i++)
		{
			layers.push_back(Matrix(this->layerCount[i], 1));
			weights.push_back(Matrix(this->layerCount[i], this->layerCount[i - 1]));
			bias.push_back(Matrix(this->layerCount[i], 1));
		}

		for (int i = 0; i < weights.size(); i++)
		{
			weights[i].randomize();
			bias[i].randomize();
		}
	}

	std::vector<double> feedForward(std::vector<double> inputs)
	{

		for (int i = 0; i < layers[0].matrix.size(); i++)
		{
			layers[0].matrix[i][0] = inputs[i];
		}

		for (int i = 1; i < layers.size(); i++)
		{

			layers[i].matrix = Matrix::multiply(weights[i - 1], layers[i - 1]);

			layers[i].add(bias[i - 1]);
			if (activation[i - 1] == "relu")
				layers[i].map(relu);
			else if (activation[i - 1] == "sigmoid")
				layers[i].map(sigmoid);
			else if (activation[i - 1] == "tanh")
				layers[i].map(tanh);
			else if (activation[i - 1] == "softmax")
			{
				double su = Matrix::expSum(layers[i]);
				for (int k = 0; k < layers[i].matrix.size(); k++)
					for (int j = 0; j < layers[i].matrix[0].size(); j++)
						layers[i].matrix[k][j] = softmax(layers[i].matrix[k][j], su);
			}
		}

		return Matrix::oneDArray(layers.back());
	}

	void print()
	{

		std::cout << "Layers" << '\n';

		for (int i = 0; i < layers.size(); i++)
			layers[i].print();

		std::cout << "Weights" << '\n';

		for (int j = 0; j < weights.size(); j++)
			weights[j].print();

		std::cout << "Bias" << '\n';

		for (int j = 0; j < bias.size(); j++)
			bias[j].print();
	}
};