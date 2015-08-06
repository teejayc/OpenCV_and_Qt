#ifndef SALT_H
#define SALT_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Salt
{
private:
    static Salt* instance;

public:
    Salt();

    void salt(const Mat& inputImage, Mat& outputImage, unsigned int amount);

    static Salt* getInstance() {
        if(!instance) {
            instance = new Salt;
        }
        return instance;
    }

    static void destroy() {
        if(instance) {
            delete instance;
        }
    }
};

#endif // SALT_H
