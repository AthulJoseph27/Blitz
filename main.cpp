#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include "NeuralNetwork.h"
#include "miscellaneousFunctions.h"
#include "CNN.h"
using namespace std;

//clang++ $(pkg-config --cflags --libs opencv4) -std=c++14  main.cpp

int main()
{

	vector<string> LABELS = {"CIRCLE", "SQUARE", "TRIANGLE"};

	NeuralNetwork nn = NeuralNetwork({784, 64, 3}, {"sigmoid", "sigmoid"});

	std::string dir = "data/circle/";
	std::vector<std::vector<std::vector<double>>> data_labels;
	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "circle" + tmp + ".png";
		data_labels.push_back({Flatten(readGrayImage(tmp)), {1, 0, 0}});
	}

	dir = "data/square/";

	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "square" + tmp + ".png";
		data_labels.push_back({Flatten(readGrayImage(tmp)), {0, 1, 0}});
	}

	dir = "data/triangle/";

	for (int i = 1; i <= 1000; i++)
	{
		std::string tmp = std::to_string(i);
		while (tmp.size() < 4)
			tmp = "0" + tmp;
		tmp = dir + "triangle" + tmp + ".png";
		data_labels.push_back({Flatten(readGrayImage(tmp)), {0, 0, 1}});
	}
	std::cout << "Loaded Data. Training..." << std::endl;
	nn.train(data_labels, "grayImage");
	// nn.saveModel("model_00");
	// nn.readModel("model_00");
	srand(time(NULL));
	for (int i = 1000; i < 1020; i++)
	{
		int k = rand() % 3;
		if (k == 0)
		{
			std::string tmp = "triangle" + std::to_string(i);
			tmp += ".png";
			cv::Mat image = readColorImage("data/triangle/" + tmp);
			vector<double> prd = Matrix::oneDArray(nn.predict(Flatten(readGrayImage("data/triangle/" + tmp))));
			int index = argMax(prd);
			double total = 0;
			for (double d : prd)
				total += d;
			double percentage = 0;
			stringstream ss;
			ss << std::fixed << std::setprecision(2) << prd[index] * 100.0 / total;
			string result = LABELS[index] + " - " + ss.str() + "%";
			cv::Mat outImg;
			cv::resize(image, outImg, cv::Size(), 20, 20);
			putText(outImg, result, cv::Point(20, 50),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 2.5, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
			imshow("Blitz", outImg);
			int k = cv::waitKey(0);
		}
		else if (k == 1)
		{
			std::string tmp = "square" + std::to_string(i);
			tmp += ".png";
			cv::Mat image = readColorImage("data/square/" + tmp);
			nn.predict(Flatten(readGrayImage("data/square/" + tmp)));
			vector<double> prd = Matrix::oneDArray(nn.predict(Flatten(readGrayImage("data/square/" + tmp))));
			int index = argMax(prd);
			double total = 0;
			for (double d : prd)
				total += d;
			double percentage = 0;
			stringstream ss;
			ss << std::fixed << std::setprecision(2) << prd[index] * 100.0 / total;
			string result = LABELS[index] + " - " + ss.str() + "%";
			cv::Mat outImg;
			cv::resize(image, outImg, cv::Size(), 20, 20);
			putText(outImg, result, cv::Point(20, 50),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 2.5, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
			imshow("Blitz", outImg);
			int k = cv::waitKey(0);
		}
		else
		{
			std::string tmp = "circle" + std::to_string(i);
			tmp += ".png";
			cv::Mat image = readColorImage("data/circle/" + tmp);
			nn.predict(Flatten(readGrayImage("data/circle/" + tmp)));
			vector<double> prd = Matrix::oneDArray(nn.predict(Flatten(readGrayImage("data/circle/" + tmp))));
			int index = argMax(prd);
			double total = 0;
			for (double d : prd)
				total += d;
			double percentage = 0;
			stringstream ss;
			ss << std::fixed << std::setprecision(2) << prd[index] * 100.0 / total;
			string result = LABELS[index] + " - " + ss.str() + "%";
			cv::Mat outImg;
			cv::resize(image, outImg, cv::Size(), 20, 20);
			putText(outImg, result, cv::Point(20, 50),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 2.5, cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
			imshow("Blitz", outImg);
			int k = cv::waitKey(0);
		}
	}

	// int accuracy = 0;

	// std::cout << accuracy << std::endl;
	// std::cout << (((double)accuracy * 100) / data_labels.size()) << std::endl;

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
