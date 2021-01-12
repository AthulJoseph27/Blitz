#pragma once

#include "opencv2/opencv.hpp"
#include <vector>
#include <stdint.h>

cv::Mat readGrayImage(std::string fileName)
{

    cv::Mat image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    return image;
}

// cv::Mat MaxPooling2D(cv::Mat image){

// }

std::vector<double> flatten(cv::Mat image)
{

    if (image.empty())
        return image;

    std::vector<double> result;

    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
            result.push_back(image.at<uint8_t>(i, j));

    return result;
}
