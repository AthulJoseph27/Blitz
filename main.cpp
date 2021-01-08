#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <algorithm>
#include <random>
#include "Matrix.h"
#include "NeuralNetwork.h"
using namespace std;

int main()
{
	vector<vector<double>> labels = {{1}, {1}, {0}, {0}};
	vector<vector<double>> data = {{1, 0}, {0, 1}, {1, 1}, {0, 0}};
	vector<vector<double>> labelsT = {};
	vector<vector<double>> dataT = {};
	vector<vector<vector<double>>> T = {};
	for (int i = 0; i < 5000; i++)
	{
		for (int j = 0; j < 4; j++)
			T.push_back({data[j], labels[j]});
	}
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(T), std::end(T), rng);
	std::shuffle(begin(T), end(T), rng);
	for (auto i : T)
	{
		dataT.push_back(i[0]);
		labelsT.push_back(i[1]);
	}
	NeuralNetwork nn = NeuralNetwork({2, 3, 2, 1}, {"sigmoid", "sigmoid", "sigmoid"});
	nn.train(labelsT, dataT, 1);

	cout << "***********" << endl;
	cout << endl;
	for (auto i : data)
	{
		cout << i[0] << " xor " << i[1] << " = " << endl;
		nn.predict(i);
	}
	return 0;
}
