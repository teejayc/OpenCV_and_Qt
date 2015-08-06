#include "linefinder.h"

LineFinder* LineFinder::instance = 0;


void LineFinder::setAccResolution(double dRho, double dTheta) {
    deltaRho = dRho;
    deltaTheta = dTheta;
}

void LineFinder::setMinVote(int minv) {
    minVote = minv;
}

void LineFinder::setLineLengthAndGap(double length, double gap) {
    minLength = length;
    maxGap = gap;
}

vector<Vec4i> LineFinder::findLines(const Mat& binary) {
    lines.clear();
    HoughLinesP(binary, lines,
                deltaRho, deltaTheta, minVote,
                minLength, maxGap);
    return lines;
}

void LineFinder::drawDetectedLines(const Mat& originalImage, Mat& processedImage,
                                   Scalar color) {
    originalImage.copyTo(processedImage);

    cvtColor(processedImage, processedImage, CV_GRAY2BGR);

    vector<Vec4i>::const_iterator it = lines.begin();
    vector<Vec4i>::const_iterator end = lines.end();

    while(it != end) {
        Point pt1((*it)[0], (*it)[1]);
        Point pt2((*it)[2], (*it)[3]);
        line(processedImage, pt1, pt2, color);
        ++it;
    }
}

