/// @file VirtualPainter.h
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <X11/Xlib.h>
#include <tuple>
#include <cstdlib>
#define max 255
#define min 0
#define thick_max 20
#define thick_min 2
#include <unistd.h>
using namespace cv;
using namespace std;

class VirtualPainter
{

public: 
VirtualPainter();
int processimage();



private:
int screen_height;
int screen_width;
int image_width;
int image_height;
Display* dpy; 
int scr;
Window root_window;
Mat rgb_hsv(Mat  imgHSV); // This function is used to convert RGB TO HSV
Mat pre_process1(Mat  imgHSV); // This function is doing Preprocessing like thresholding, erode and dilate
tuple<int, int> moments1(Mat imgThresholded2); //  This function is used to calculate the moments 
tuple<int, int, int, int> mousepointer( int x, int y, Mat imgThresholded2); //This  function is for mousepointer
Mat imgTmp;
Mat imgLines;
Mat imgOriginal;
int thickness;
Scalar pen_color;
float iLastX = 0; 
float iLastY = 0;


};

