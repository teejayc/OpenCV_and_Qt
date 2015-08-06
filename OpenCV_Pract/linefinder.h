#ifndef LINEFINDER_H
#define LINEFINDER_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

using namespace cv;
class LineFinder
{
private:
    static LineFinder* instance;

    static const double PI = 3.141592;

    vector<Vec4i> lines;

    double deltaRho;
    double deltaTheta;

    int minVote;

    double minLength;
    double maxGap;



public:
    static LineFinder* getInstance() {
        if(!instance) {
            instance = new LineFinder;
        }
        return instance;
    }

    static void destroy() {
        if(instance) {
            delete instance;
            instance = 0;
        }
    }

    LineFinder() : deltaRho(1), deltaTheta(PI / 180),
        minVote(10), minLength(0.), maxGap(0.) {}

    void setAccResolution(double dRho, double dTheta);

    void setMinVote(int minv);

    void setLineLengthAndGap(double length, double gap);

    vector<Vec4i> findLines(const Mat& binary);

    void drawDetectedLines(const Mat& originalImage, Mat& processedImage, Scalar color = Scalar(255, 0, 0));
};

#endif // LINEFINDER_H
