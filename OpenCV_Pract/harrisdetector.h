#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class HarrisDetector
{
    static HarrisDetector* instance;

    Mat cornerStrength;
    Mat cornerTh;
    Mat localMax;

    int neighbourhood;
    int aperture;
    double k;
    double maxStrength;
    double threshold;
    int nonMaxSize;
    Mat kernel;


public:
    HarrisDetector() : neighbourhood(3), aperture(3),
        k(0.01), maxStrength(0.0),
        threshold(0.01), nonMaxSize(3) {
        setLocalMaxWindowSize(nonMaxSize);
    }

    static HarrisDetector* getInstance() {
        if(!instance) {
            instance = new HarrisDetector;
        }
        return instance;
    }

    static void destroy() {
        if(instance) {
            delete instance;
            instance = 0;
        }
    }

    void detect(const Mat& image);
};

#endif // HARRISDETECTOR_H
