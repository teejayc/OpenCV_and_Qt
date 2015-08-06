#include "sharpen.h"

Sharpen* Sharpen::instance = 0;

Sharpen::Sharpen() {}

void Sharpen::sharpen(const Mat& input, Mat& output) {
    output.create(input.size(), input.type());

    unsigned int numRows = input.rows - 1;
    unsigned int numCols = input.cols - 1;


    for(unsigned int i = 1; i < numRows; ++i) {
        const uchar* prev = input.ptr<uchar>(i);
        const uchar* curr = input.ptr<uchar>(i);
        const uchar* next = input.ptr<uchar>(i);

        uchar* outputRow = output.ptr<uchar>(i);
        for(unsigned int j = 1; j < numCols; ++j) {
            outputRow[j] = cv::saturate_cast<uchar>(
                        5 * curr[j] - curr[j - 1] - curr[j + 1]
                        - prev[j] - next[j]);
        }
    }

    output.row(0).setTo(Scalar(0));
    output.row(numRows).setTo(Scalar(0));
    output.col(0).setTo(Scalar(0));
    output.col(numCols).setTo(Scalar(0));
}
