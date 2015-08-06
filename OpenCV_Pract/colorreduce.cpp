#include "colorreduce.h"

ColorReduce* ColorReduce::instance = 0;

ColorReduce::ColorReduce() {}

void ColorReduce::colorReduce(Mat& inputImg, Mat& outputImg, unsigned int div) {
    //resize outputImg
    outputImg.create(inputImg.size(), inputImg.type());
    //inputImg.copyTo(outputImg);

    unsigned int numRows = inputImg.rows;
    unsigned int numEltsPerRow = inputImg.cols * inputImg.channels();

    for(unsigned int i = 0; i < numRows; ++i) {

        const uchar* inputRow = inputImg.ptr<uchar>(i);
        uchar* outputRow = outputImg.ptr<uchar>(i);

        for(unsigned int j = 0; j < numEltsPerRow; ++j) {
            outputRow[j] = inputRow[j] / div * div + div / 2;
        }
    }
}
