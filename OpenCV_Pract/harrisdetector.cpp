#include "harrisdetector.h"

HarrisDetector* HarrisDetector::instance = 0;

HarrisDetector::HarrisDetector()
{

}

void HarrisDetector::detect(const Mat& image) {
    cornerHarris(image, cornerStrength,
                 neighbourhood,
                 aperture,
                 k);

    double minStrength;
    minMaxLoc(cornerStrength, &minStrength,
              &maxStrength);

    Mat dilated;
    dilate(cornerStrength, dilated, Mat());
    compare(cornerStrength, dilated, localMax, CV::CMP_EQ);
}
