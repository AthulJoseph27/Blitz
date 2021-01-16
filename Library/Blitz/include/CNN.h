#pragma once

#include <opencv2/opencv.hpp>

cv::Mat readGrayImage(std::string fileName);
cv::Mat readColorImage(std::string fileName);
std::vector<double> Flatten(cv::Mat image);
cv::Mat MaxPooling2D(cv::Mat image, int size, int stride);
