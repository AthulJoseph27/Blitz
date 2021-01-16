#pragma once

#include <vector>
#include <map>
#include "Matrix.h"

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
    void readConfiguration();

public:
    NeuralNetwork();
    NeuralNetwork(std::vector<int> layerCount, std::vector<std::string> activation);
    Matrix feedForward(std::vector<double> input);
    void Normalize(std::vector<std::vector<std::vector<double>>> &data_labels, std::string function);
    void trainBatch(std::vector<std::vector<double>> &labels, std::vector<std::vector<double>> &data, int start, int end);
    void shuffleData(std::vector<std::vector<std::vector<double>>> &data);
    void train(std::vector<std::vector<std::vector<double>>> &data_labels, std::string normalizingFunction);
    Matrix predict(std::vector<double> data);
    void saveModel(std::string fileName);
    void readModel(std::string fileName);
    void print();
};