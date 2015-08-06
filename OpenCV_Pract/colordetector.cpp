#include "colordetector.h"

ColorDetector* ColorDetector::instance = 0;

ColorDetector::ColorDetector() : minDist(100) {
    targetColor[0]
            = targetColor[1]
            = targetColor[2]
            = 0;
}

void ColorDetector::setColorDistanceThreshold(int distance) {
    if(distance < 0) {
        minDist = 0;
    }
    else {
        minDist = distance;
    }
}

int ColorDetector::getColorDistanceThreshold() const {
    return minDist;
}

void ColorDetector::setTargetColor(unsigned char red,
                    unsigned char green,
                    unsigned char blue) {
    Mat temp(1, 1, CV_8UC3);
    temp.at<Vec3b>(0, 0)[0] = blue;
    temp.at<Vec3b>(0, 0)[1] = green;
    temp.at<Vec3b>(0, 0)[2] = red;
    cvtColor(temp, temp, CV_BGR2Lab);
    targetColor = temp.at<Vec3b>(0, 0);
}

void ColorDetector::setTargetColor(Vec3b color) {
    targetColor = color;
}

Vec3b ColorDetector::getTargetColor() const {
    return targetColor;
}

int ColorDetector::getDistance(const Vec3b &color) const {
    return abs(color[0] - targetColor[0]) +
            abs(color[1] - targetColor[1]) +
            abs(color[2] - targetColor[2]);
}

void ColorDetector::colorDetector(const Mat& input, Mat& output) {
    output.create(input.rows, input.cols, CV_8U);

    Mat labMat;
    cvtColor(input, labMat, CV_BGR2Lab);

    Mat_<Vec3b>::const_iterator it = labMat.begin<Vec3b>();
    Mat_<Vec3b>::const_iterator itend = labMat.end<Vec3b>();
    Mat_<uchar>::iterator itout = output.begin<uchar>();

    for(; it != itend; ++it, ++itout) {
        if(getDistance(*it) < minDist) {
            *itout = 255;
        }
        else {
            *itout = 0;
        }
    }
}
