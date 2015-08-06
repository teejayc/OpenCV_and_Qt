#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::IMAGE_FILE_PATH
        = "/home/teejayc/Work_Place/Images";

const string MainWindow::ZACH1 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/Zachary_Quinto_2012.jpg";
const string MainWindow::ZACH2 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/Zachary_Quinto(a).jpg";
const string MainWindow::ZACH3 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/Zachary-Quinto_GettyImages.jpg.644x466_q100.jpg";
const string MainWindow::ZACH4 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/ZacharyQuintoSS218_3.jpeg";
const string MainWindow::ZACH5 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/Zachary-Quinto-zachary-quinto-6665179-1695-2560.jpg";
const string MainWindow::ZACH6 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/zachary20quinto204.jpg";
const string MainWindow::ZACH7 = "/Users/taejungchang/Google Drive/My Storage/Work_Place/Image_Processing/Images/ZacharyQuintoSS218_3.jpeg";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
//    if(!originalImage.data) {
//        QString fileName = QFileDialog::getOpenFileName(
//                    this,
//                    tr("Open Image"),
//                    IMAGE_FILE_PATH,
//                    "Image Files (*.png *.bmp *.jpg *.jpeg)");

//        originalImage = imread(fileName.toStdString());

//        if(originalImage.rows > ui->Original_label->height()) {
//            cv::resize(originalImage,
//                       originalImage,
//                       Size(originalImage.cols * ui->Original_label->height() / originalImage.rows,
//                            ui->Original_label->height()));
//        }

//        if(originalImage.cols > ui->Original_label->width()) {
//            cv::resize(originalImage,
//                       originalImage,
//                       Size(ui->Original_label->width(),
//                            originalImage.rows * ui->Original_label->width() / originalImage.cols));
//        }
//    }

//    projectToLabel(originalImage, ui->Original_label, CV_BGR2RGB);

    if(!originalImage.data) {
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open Image"),
                    IMAGE_FILE_PATH,
                    "Image File (*.png *.jpeg *.jpg *.bmp)");

        originalImage = imread(fileName.toStdString());

        if(originalImage.rows > ui->Original_label->height()) {
            cv::resize(originalImage,
                       originalImage,
                       Size(originalImage.cols * ui->Original_label->height() / originalImage.rows,
                            ui->Original_label->height()));
        }

        if(originalImage.cols > ui->Original_label->width()) {
            cv::resize(originalImage,
                       originalImage,
                       Size(ui->Original_label->width(),
                            originalImage.rows * ui->Original_label->width() / originalImage.cols));
        }

        projectToLabel(originalImage, ui->Original_label, CV_BGR2RGB);
    }
}

void MainWindow::projectToLabel(const Mat& image, QLabel* ui, unsigned int convertingFlag) {
//    cvtColor(image, forQLabelMat, convertingFlag);

//    forQLabelQImage = QImage(forQLabelMat.data,
//                            forQLabelMat.cols,
//                            forQLabelMat.rows,
//                            forQLabelMat.step,
//                            QImage::Format_RGB888);

//    ui->setPixmap(QPixmap::fromImage(forQLabelQImage));

    cvtColor(image, forQLabelMat, convertingFlag);

    forQLabelQImage = QImage(forQLabelMat.data,
                             forQLabelMat.cols,
                             forQLabelMat.rows,
                             forQLabelMat.step,
                             QImage::Format_RGB888);

    ui->setPixmap(QPixmap::fromImage(forQLabelQImage));
}

void MainWindow::on_actionOpen_Image_triggered() {
    openImage();
}

void MainWindow::on_actionSalt_triggered()
{
    openImage();

    //process
    Salt::getInstance()->salt(originalImage, processedImage, 7777);

    //project to label
    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);

    Salt::destroy();
}

void MainWindow::on_openImage_pushButton_clicked()
{
    openImage();
}

void MainWindow::on_actionColor_Reduce_triggered()
{
    openImage();

    ColorReduce::getInstance()->colorReduce(originalImage, processedImage);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);

    ColorReduce::destroy();
}

void MainWindow::on_actionSharpen_triggered()
{
    openImage();

    cvtColor(originalImage, originalImage, CV_BGR2GRAY);

    Sharpen::getInstance()->sharpen(originalImage, processedImage);

    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);

    Sharpen::destroy();
}


void MainWindow::on_actionOverlay_triggered()
{
    openImage();

    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Second Image"),
                IMAGE_FILE_PATH,
                "Image Files (*.jpg *.jpeg *.png *.bmp)");

    originalImage2 = imread(fileName.toStdString());
    cv::resize(originalImage2, originalImage2, Size(originalImage.cols, originalImage.rows));

    //addWeighted(originalImage, 0.5, originalImage2, 0.5, 0., processedImage);
    processedImage = 0.5 * originalImage + 0.5 * originalImage2;

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);
}

void MainWindow::on_actionAdd_Logo_triggered()
{
    openImage();
    originalImage.copyTo(processedImage);
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Logo"),
                IMAGE_FILE_PATH,
                "Image Files (*.jpeg *.jpg *.bmp *.png)");
    Mat logo = imread(fileName.toStdString());

    Mat imageROI = processedImage(Rect(0, 0, logo.cols, logo.rows));

    addWeighted(imageROI, 1.0, logo, 0.3, 0., imageROI);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);

}

void MainWindow::on_actionAdd_Logo2_triggered()
{
    openImage();
    originalImage.copyTo(processedImage);
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Logo"),
                IMAGE_FILE_PATH,
                "Image Files (*.jpeg *.jpg *.bmp *.png)");
    Mat logo = imread(fileName.toStdString());

    Mat imageROI = processedImage(Rect(0, 0, logo.cols, logo.rows));

    Mat mask = imread(fileName.toStdString(), 0);

    logo.copyTo(imageROI, mask);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);
}


void MainWindow::on_actionColor_Detect_triggered()
{
    openImage();
    ColorDetector::getInstance()->setTargetColor(130, 190, 230);
    ColorDetector::getInstance()->colorDetector(originalImage, processedImage);
    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
}


void MainWindow::on_SelectColor_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if(color.isValid()) {
        ColorDetector::getInstance()->setTargetColor(color.red(), color.green(), color.blue());
    }
}


void MainWindow::on_Threshold_horizontalSlider_sliderMoved(int position)
{
    ColorDetector::getInstance()->setColorDistanceThreshold(ui->Threshold_horizontalSlider->value());
    ColorDetector::getInstance()->colorDetector(originalImage, processedImage);
    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
}

void MainWindow::on_processProcessed_pushButton_clicked()
{
    processedImage.copyTo(originalImage);
    if(originalImage.channels() == 1) {
        projectToLabel(originalImage, ui->Original_label, CV_GRAY2RGB);
    }
    else if(originalImage.channels() == 3) {
        projectToLabel(originalImage, ui->Original_label, CV_BGR2RGB);
    }
}

void MainWindow::on_actionErosion_triggered()
{
    if(!originalImage.data || !processedImage.data) {
        cout << "Load Image first!" << endl;
    }
    else {
        erode(originalImage, processedImage, Mat());
        projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
    }

}

void MainWindow::on_actionDilate_triggered()
{
    if(!originalImage.data || !processedImage.data) {
        cout << "Load Image first!" << endl;
    }
    else {
        dilate(originalImage, processedImage, Mat());
        projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
    }
}

void MainWindow::on_actionOpening_triggered()
{
    if(!originalImage.data || !processedImage.data) {
        cout << "Load Image first!" << endl;
    }
    else {
        Mat element5(5, 5, CV_8U, Scalar(1));
        morphologyEx(originalImage, processedImage, MORPH_OPEN, element5);
        projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
    }
}

void MainWindow::on_actionClosing_triggered()
{
    if(!originalImage.data || !processedImage.data) {
        cout << "Load Image first!" << endl;
    }
    else {
        Mat element5(5, 5, CV_8U, Scalar(1));
        morphologyEx(originalImage, processedImage, MORPH_CLOSE, element5);
        projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
    }
}

void MainWindow::on_actionMean_triggered()
{
    openImage();

    blur(originalImage, processedImage, Size(5, 5));

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);
}


void MainWindow::on_actionGaussian_triggered()
{
    openImage();

    GaussianBlur(originalImage, processedImage, Size(5, 5), 0);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);

}

void MainWindow::on_actionMedian_triggered()
{
    openImage();

    medianBlur(originalImage, processedImage, 5);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);

}

void MainWindow::on_actionCanny_triggered()
{
    openImage();
    Canny(originalImage,
          processedImage,
          125,
          350);
    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
}

void MainWindow::on_lowThreshold_horizontalSlider_sliderMoved(int position)
{
    Canny(originalImage,
          processedImage,
          ui->lowThreshold_horizontalSlider->value(),
          ui->highThreshold_horizontalSlider->value());
    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
}

void MainWindow::on_highThreshold_horizontalSlider_actionTriggered(int action)
{
    Canny(originalImage,
          processedImage,
          ui->lowThreshold_horizontalSlider->value(),
          ui->highThreshold_horizontalSlider->value());
    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2RGB);
}

void MainWindow::on_actionLine_detection_triggered()
{
    const double PI = 3.141592;

    //TODO: alert if the original image is not from canny
    vector<Vec2f> lines;

    HoughLines(originalImage, lines, 1, PI / 180, 65);

    //draw lines
    vector<Vec2f>::const_iterator it = lines.begin();
    vector<Vec2f>::const_iterator end = lines.end();
    while(it != end) {
        float rho = (*it)[0];
        float theta = (*it)[1];

        //QUESTION: how to set up points?
        //vertical line
        if(theta < PI / 4. || theta > 3. * PI / 4.) {
            //point of intersection of the ine with first row
            Point pt1(rho / cos(theta), 0);
            //point of intersection of the line with last row
            Point pt2((rho - originalImage.rows * sin(theta))
                      / cos(theta), originalImage.rows);
            line(processedImage, pt1, pt2, Scalar(255), 1);
        }
        //horizontal line
        else {
            Point pt1(0, rho / sin(theta));
            Point pt2(originalImage.cols, (rho - originalImage.cols * cos(theta) / sin(theta)));
            line(processedImage, pt1, pt2, Scalar(255), 1);
        }
        ++it;
    }

    projectToLabel(processedImage, ui->Processed_label, CV_GRAY2BGR);
}

void MainWindow::on_actionProbabilistic_Hough_Transform_triggered()
{
    LineFinder::getInstance()->setLineLengthAndGap(10, 10);
    LineFinder::getInstance()->setMinVote(30);

    LineFinder::getInstance()->findLines(originalImage);

    LineFinder::getInstance()->drawDetectedLines(originalImage, processedImage);

    projectToLabel(processedImage, ui->Processed_label, CV_BGR2RGB);
}
