#include <iostream>
#include <vector>
#include "utils.h"
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("usage: %s <path_of_image>\n", argv[0]);
        return 0;
    }

    cv::Mat image = cv::imread(argv[1]);
    ColorCollection ccl(image);
    ccl.kMeans(8);
    return 0;
}