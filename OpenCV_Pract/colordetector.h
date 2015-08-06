#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ColorDetector
{
private:
    static ColorDetector* instance;

    unsigned int minDist;
    Vec3b targetColor;

public:
    ColorDetector();

    static ColorDetector* getInstance() {
        if(!instance) {
            instance = new ColorDetector;
        }
        return instance;
    }

    static void destroy() {
        if(instance) {
            delete instance;
            instance = 0;
        }
    }

    void setColorDistanceThreshold(int distance);

    int getColorDistanceThreshold() const;

    void setTargetColor(unsigned char red,
                        unsigned char green,
                        unsigned char blue);

    void setTargetColor(Vec3b color);

    Vec3b getTargetColor() const;

    int getDistance(const Vec3b& color) const;

    void colorDetector(const Mat& input, Mat& output);
};

#endif // COLORDETECTOR_H
