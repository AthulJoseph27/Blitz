#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include "Matrix.h"
#include "NeuralNetwork.h"
#include "CNN.h"
using namespace std;

int main()
{

	NeuralNetwork nn = NeuralNetwork({4096, 256, 64, 3}, {"sigmoid", "sigmoid", "sigmoid"});

	std::string dir = "data/circle/";
	std::vector<std::vector<std::vector<double>>> data_labels;
	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "circle" + tmp + ".png";
		data_labels.push_back({flatten(readGrayImage(tmp)), {1, 0, 0}});
	}

	dir = "data/square/";

	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "square" + tmp + ".png";
		data_labels.push_back({flatten(readGrayImage(tmp)), {0, 1, 0}});
	}

	dir = "data/triangle/";

	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "triangle" + tmp + ".png";
		data_labels.push_back({flatten(readGrayImage(tmp)), {0, 0, 1}});
	}
	std::cout << "Loaded Data. Training..." << std::endl;
	nn.train(data_labels, "grayImage");
	nn.saveModel("model_00");
	nn.predict(flatten(readGrayImage("data/triangle/triangle0001.png")));
	nn.predict(flatten(readGrayImage("data/square/square0001.png")));
	nn.predict(flatten(readGrayImage("data/circle/circle0001.png")));

	// vector<vector<double>> labels = {{1}, {1}, {0}, {0}};
	// vector<vector<double>> data = {{1, 0}, {0, 1}, {1, 1}, {0, 0}};
	// vector<vector<double>> labelsT = {};
	// vector<vector<double>> dataT = {};
	// vector<vector<vector<double>>> T = {};
	// vector<vector<vector<double>>> data_labels;
	// for (int i = 0; i < 1; i++)
	// {
	// 	for (int j = 0; j < 4; j++)
	// 		data_labels.push_back({data[j], labels[j]});
	// }

	// NeuralNetwork nn = NeuralNetwork({2, 3, 2, 1}, {"sigmoid", "sigmoid", "sigmoid"});
	// nn.train(data_labels, "non");

	// // cout << "***********" << endl;
	// // cout << endl;
	// for (auto i : data)
	// {
	// 	cout << i[0] << " xor " << i[1] << " = " << endl;
	// 	nn.predict(i);
	// }
	return 0;
}
