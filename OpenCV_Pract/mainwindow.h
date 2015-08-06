#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//OpenCV headers
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//QT headers
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QColorDialog>

//C++ headers
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>           //PI, sin, cos

//classes
#include "salt.h"
#include "colorreduce.h"
#include "sharpen.h"
#include "colordetector.h"
#include "linefinder.h"

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void openImage();

    void projectToLabel(const Mat& image, QLabel* ui, unsigned int covertingFlag);

    void on_actionOpen_Image_triggered();

    void on_actionSalt_triggered();

    void on_pushButton_clicked();

    void on_openImage_pushButton_clicked();

    void on_actionColor_Reduce_triggered();

    void on_actionSharpen_triggered();

    void on_actionOverlay_triggered();

    void on_actionAdd_Logo_triggered();

    void on_actionAdd_Logo2_triggered();

    void on_actionColor_Detect_triggered();

    void on_SelectColor_pushButton_clicked();

    void on_Threshold_horizontalSlider_sliderMoved(int position);

    void on_processProcessed_pushButton_clicked();

    void on_actionErosion_triggered();

    void on_actionDilate_triggered();

    void on_actionOpening_triggered();

    void on_actionClosing_triggered();

    void on_actionMedian_triggered();

    void on_actionMean_triggered();

    void on_actionGaussian_triggered();

    void on_horizontalSlider_sliderMoved(int position);

    void on_actionCanny_triggered();

    void on_lowThreshold_horizontalSlider_sliderMoved(int position);

    void on_highThreshold_horizontalSlider_actionTriggered(int action);

    void on_actionLine_detection_triggered();

    void on_actionProbabilistic_Hough_Transform_triggered();

private:
    Ui::MainWindow *ui;

    static const QString IMAGE_FILE_PATH;
    static const string ZACH1;
    static const string ZACH2;
    static const string ZACH3;
    static const string ZACH4;
    static const string ZACH5;
    static const string ZACH6;
    static const string ZACH7;

    QString imageFileName;
    Mat originalImage;
    Mat originalImage2;
    Mat originalBW;
    Mat forQLabelMat;
    QImage forQLabelQImage;

    Mat processedImage;
};

#endif // MAINWINDOW_H
