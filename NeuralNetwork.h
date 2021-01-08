#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>
#include <time.h>
#include <fstream>
#include "Matrix.h"
#include "ActivationFunctions.h"
#include "LossFunctions.h"

class NeuralNetwork
{
private:
	std::vector<int> layerCount;
	std::vector<Matrix> layers;
	std::vector<Matrix> weights;
	std::vector<Matrix> bias;
	std::vector<std::string> activation;
	std::map<std::string, double> configurations; // {learning_rate, no_of_steps}

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

	Matrix feedForward(std::vector<double> input)
	{

		for (int i = 0; i < layers[0].matrix.size(); i++)
		{
			layers[0].matrix[i][0] = input[i];
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

		return layers.back();
	}

	// void loadConfig()
	// {
	// 	fstream file;
	// 	file.open("Config.txt",ios::in);
	// 	while(!file.eof){

	// 	}
	// }

	void trainBatch(std::vector<std::vector<double>> &labels, std::vector<std::vector<double>> &data, int start, int end)
	{
		Matrix batchError = Matrix(layers.back().matrix.size(), 1);

		for (long i = start; i < end; i++)
		{
			feedForward(data[i]);
			batchError.add(MSE(labels[i], Matrix::oneDArray(layers.back())));
		}
		batchError.scale(1.0 / ((double)end - (double)start));

		std::vector<Matrix> errors;

		errors.push_back(batchError);

		for (int i = weights.size() - 1; i >= 0; i--)
		{
			// delta W = lr * derivative of current layer * current error * transpose of previous layer;
			// delta B =  lr * derivative of current layer * current error;

			Matrix currentLayer = Matrix(layers[i + 1].matrix);
			if (activation[i] == "sigmoid")
				currentLayer.map(derivativeSigmoid);
			else if (activation[i] == "relu")
				currentLayer.map(derivativeRelu);
			else if (activation[i] == "tanh")
				currentLayer.map(derivativeTanh);
			else
				std::invalid_argument("Invalid activation function");

			currentLayer.hadamadProduct(errors.back());
			Matrix delta = Matrix(currentLayer.matrix);
			delta.scale(0.1); // Replace 0.001 with configurations["lr"]
			bias[i].add(delta);
			Matrix previousLayer = Matrix(layers[i].matrix);
			previousLayer.transpose();
			delta.multiply(previousLayer);
			weights[i].add(delta);
			// Confirm if previous error should be computed before updating weights or not
			Matrix previousLayerErrors = Matrix(weights[i]);
			previousLayerErrors.transpose();
			previousLayerErrors.multiply(errors.back());
			errors.push_back(previousLayerErrors);
		}
	}

	void train(std::vector<std::vector<double>> &labels, std::vector<std::vector<double>> &data, int batchSize)
	{
		if (batchSize > data.size())
		{
			trainBatch(labels, data, 0, data.size());
		}
		for (long i = batchSize; i < data.size(); i += batchSize)
		{
			trainBatch(labels, data, i - batchSize, i);
		}
	}

	void predict(std::vector<double> data)
	{
		feedForward(data).print();
		std::cout << std::endl;
	}
	void print()
	{

		std::cout << "Layers"
				  << "\n\n";

		for (int i = 0; i < layers.size(); i++)
			layers[i].print();

		std::cout << "Weights"
				  << "\n\n";

		for (int j = 0; j < weights.size(); j++)
			weights[j].print();

		std::cout << "Bias"
				  << "\n\n";

		for (int j = 0; j < bias.size(); j++)
			bias[j].print();
	}
};