
#pragma once
#include <iostream>
#include"opencv2/opencv.hpp"
#include "nanodet.h"
int main()
{
    //src的尺寸最好是288*288
    cv::Mat src = cv::imread("model/girl.jpg",-1);
    NanoDet g_nanodet;
    const char* modelName = "model/hair";

    g_nanodet.load(modelName, false);
    g_nanodet.draw(src);

    std::cout << "Hello World!\n";
}

