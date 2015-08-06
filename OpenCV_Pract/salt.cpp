#include "salt.h"


Salt* Salt::instance = 0;

Salt::Salt()
{

}



void Salt::salt(const Mat &inputImage, Mat &outputImage, unsigned int amount) {
    inputImage.copyTo(outputImage);
    unsigned int i = 0;
    unsigned int j = 0;
    for(unsigned int k = 0; k < amount; ++k) {
        i = rand() % outputImage.rows;
        j = rand() % outputImage.cols;

        if(outputImage.channels() == 1) {
            outputImage.at<uchar>(i, j) = 255;
        }
        else if(outputImage.channels() == 3) {
            outputImage.at<Vec3b>(i, j)[0] = 225;
            outputImage.at<Vec3b>(i, j)[1] = 255;
            outputImage.at<Vec3b>(i, j)[2] = 255;
        }
    }
}
