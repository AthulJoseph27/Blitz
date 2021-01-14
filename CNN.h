#pragma once

#include "opencv2/opencv.hpp"
#include <vector>
#include <stdint.h>

cv::Mat readGrayImage(std::string fileName)
{

    cv::Mat image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
    return image;
}

cv::Mat readColorImage(std::string fileName)
{
    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);
    return image;
}
// cv::Mat MaxPooling2D(cv::Mat image){

// }

std::vector<double> Flatten(cv::Mat image)
{

    if (image.empty())
        return image;

    std::vector<double> result;

    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
            result.push_back(((double)image.at<uint8_t>(i, j)) / 255.0f);

    return result;
}

cv::Mat MaxPooling2D(cv::Mat image, int size, int stride)
{

    //Warning : Edge Case is not Handled
    if (image.empty())
        return image;

    cv::Mat result(image.rows / stride, image.cols / stride, CV_8UC1);

    for (int r = 0, row = 0; r < image.rows; r += stride, row++)
    {
        for (int c = 0, col = 0; c < image.cols; c += stride, col++)
        {

            uint8_t maxi = 0;

            for (int i = r; i < r + stride; i++)
                for (int j = c; j < c + stride; j++)
                    if (image.at<uint8_t>(i, j) > maxi)
                        maxi = image.at<uint8_t>(i, j);

            result.at<uint8_t>(row, col) = maxi;
        }
    }

    return result;
}