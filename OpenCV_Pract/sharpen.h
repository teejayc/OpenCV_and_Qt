#ifndef SHARPEN_H
#define SHARPEN_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc//imgproc.hpp>

using namespace cv;

class Sharpen
{
private:
    static Sharpen* instance;
public:
    Sharpen();
    static Sharpen* getInstance() {
        if(!instance) {
            instance = new Sharpen;
        }
        return instance;
    }

    static void destroy() {
        if(instance) {
            delete instance;
            instance = 0;
        }
    }

    //REQUIRMENT: input image is black and white
    void sharpen(const Mat& intput, Mat& output);
};

#endif // SHARPEN_H
