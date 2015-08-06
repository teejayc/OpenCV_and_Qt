#ifndef COLORREDUCE_H
#define COLORREDUCE_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ColorReduce
{
    static ColorReduce* instance;
public:
    ColorReduce();
    static ColorReduce* getInstance() {
        if(!instance) {
            instance = new ColorReduce;
        }
        return instance;
    }

    void colorReduce(Mat& inputImg, Mat& outputImg, unsigned int div = 64);

    static void destroy() {
        if(instance) {
            delete instance;
            instance = 0;
        }
    }
};

#endif // COLORREDUCE_H
