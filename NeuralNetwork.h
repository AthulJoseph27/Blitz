#pragma once

#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>
#include <random>
#include <time.h>
#include <fstream>
#include "Matrix.h"
#include "ActivationFunctions.h"
#include "LossFunctions.h"
#include "miscellaneousFunctions.h"

class NeuralNetwork
{
private:
	std::vector<int> layerCount;
	std::vector<Matrix> layers;
	std::vector<Matrix> weights;
	std::vector<Matrix> bias;
	std::vector<std::string> activation;
	std::map<std::string, double> configurations; // {learning_rate, no_of_steps}
	int accuracy = 0;
	void readConfiguration()
	{
		std::fstream file;
		file.open("configuration.txt", std::ios::in);
		std::string id;
		char c;
		double value;
		while (file >> id >> c >> value)
		{
			configurations[id] = value;
		}
		file.close();
	}

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

		readConfiguration();
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

	void Normalize(std::vector<std::vector<std::vector<double>>> &data_labels, std::string function)
	{

		if (function == "sigmoid")
		{
			for (int k = 0; k < data_labels.size(); k++)
			{
				for (int i = 0; i < data_labels[k][0].size(); i++)
					data_labels[k][0][i] = sigmoid(data_labels[k][0][i]);
			}
		}
		else if (function == "grayImage")
		{
			for (int k = 0; k < data_labels.size(); k++)
			{
				for (int i = 0; i < data_labels[k][0].size(); i++)
					data_labels[k][0][i] /= 255;
			}
		}
	}

	void trainBatch(std::vector<std::vector<double>> &labels, std::vector<std::vector<double>> &data, int start, int end)
	{
		Matrix batchError = Matrix(layers.back().matrix.size(), 1);

		for (long i = start; i < end; i++)
		{
			feedForward(data[i]);
			if (((int)labels[i][argMax(Matrix::oneDArray(layers.back()))]) == 1)
				accuracy++;
			batchError.add(DifferenceError(labels[i], Matrix::oneDArray(layers.back())));
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
			delta.scale(configurations["learning_rate"]); // Replace 0.001 with configurations["lr"]
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

	void shuffleData(std::vector<std::vector<std::vector<double>>> &data)
	{

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		auto randomEngine = std::default_random_engine{seed};
		std::shuffle(data.begin(), data.end(), randomEngine);
	}

	void train(std::vector<std::vector<std::vector<double>>> &data_labels, std::string normalizingFunction)
	{
		Normalize(data_labels, normalizingFunction);
		int batchSize, epoch;
		// double learning_rate = configurations["learning_rate"];
		batchSize = (int)configurations["batch_size"];
		epoch = (int)configurations["epoch"];
		shuffleData(data_labels);
		for (int e = 0; e < epoch; e++)
		{
			std::cout << "Epoch " << e + 1 << "\n";

			std::vector<std::vector<double>> labels = {};
			std::vector<std::vector<double>> data = {};

			for (auto i : data_labels)
			{
				labels.push_back(i[1]);
				data.push_back(i[0]);
				if (i[0].size() == 0)
					std::invalid_argument("Empty Data has been given for training!!");
			}
			// data_labels.clear();

			if (batchSize > data_labels.size())
			{
				trainBatch(labels, data, 0, data_labels.size());
				return;
			}
			for (long i = batchSize; i < data_labels.size(); i += batchSize)
			{
				printProgressBar(0, data_labels.size(), i);
				trainBatch(labels, data, i - batchSize, i);
			}
			std::cout << "\nAccuracy = " << std::fixed << std::setprecision(2) << (((double)accuracy) * 100.0) / data_labels.size() << "%\n";
			accuracy = 0;
		}
	}

	Matrix predict(std::vector<double> data)
	{
		return feedForward(data);
		// std::cout << std::endl;
	}
	void saveModel(std::string fileName)
	{
		std::fstream file;

		if (fileName.empty() || (fileName.substr(fileName.size() - 4, fileName.size() - 1) != ".txt"))
			std::invalid_argument("Invalid file name");

		file.open(fileName, std::ios::out);

		//Saving Architecture
		file << layerCount.size() << '\n';
		for (int i : layerCount)
			file << i << " ";
		file << "\n";

		//Saving Weights
		file << weights.size() << "\n";
		for (int i = 0; i < weights.size(); i++)
		{
			file << weights[i].matrix.size() << " " << weights[i].matrix[0].size() << "\n";
			for (int j = 0; j < weights[i].matrix.size(); j++)
				for (int k = 0; k < weights[i].matrix[0].size(); k++)
					file << weights[i].matrix[j][k] << " ";
			file << "\n";
		}

		//Saving Bias
		file << bias.size() << "\n";
		for (int i = 0; i < bias.size(); i++)
		{
			file << bias[i].matrix.size() << " " << bias[i].matrix[0].size() << "\n";
			for (int j = 0; j < bias[i].matrix.size(); j++)
				for (int k = 0; k < bias[i].matrix[0].size(); k++)
					file << bias[i].matrix[j][k] << " ";
			file << "\n";
		}

		//Saving Activation functions
		file << activation.size() << "\n";
		for (std::string s : activation)
			file << s << "\n";

		file.close();
	}

	void readModel(std::string fileName)
	{

		if (fileName.empty() || (fileName.substr(fileName.size() - 4, fileName.size() - 1) != ".txt"))
			std::invalid_argument("Invalid file name");

		std::fstream file;

		file.open(fileName, std::ios::in);
		long size;

		file >> size;

		layerCount.clear();
		layerCount.resize(size);

		for (int i = 0; i < size; i++)
			file >> layerCount[i];

		file >> size;

		weights.clear();
		// weights.resize(size);

		for (int k = 0; k < size; k++)
		{
			int row, col;
			file >> row >> col;
			weights.push_back(Matrix(row, col));
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					file >> weights.back().matrix[i][j];
				}
			}
		}

		file >> size;

		bias.clear();
		// bias.resize(size);

		for (int k = 0; k < size; k++)
		{
			int row, col;
			file >> row >> col;
			bias.push_back(Matrix(row, col));
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
					file >> bias.back().matrix[i][j];
		}

		file >> size;

		activation.clear();
		activation.resize(size);

		for (int i = 0; i < size; i++)
			file >> activation[i];

		file.close();
	}

	void print()
	{
		std::cout << "Configurations"
				  << "\n\n";

		for (auto it = configurations.begin(); it != configurations.end(); it++)
			std::cout << it->first << " : " << it->second << "\n";

		std::cout << "\n\n";

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