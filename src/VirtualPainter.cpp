/// @file image2.cpp
#include "VirtualPainter.h"

VirtualPainter::VirtualPainter()
 {
	dpy = XOpenDisplay(0);
	scr = XDefaultScreen(dpy); 
	root_window = XRootWindow(dpy, scr); 
	screen_height = DisplayHeight(dpy, scr);
	screen_width  = DisplayWidth(dpy, scr);
	pen_color = {0, 0, 255};
	thickness = 5;
  	std::cout << "Screen size : " <<screen_width << "x" << screen_height << std::endl; 
 }
 
	/** This  function is for mousepointer
*/
tuple<int, int, int, int> VirtualPainter:: mousepointer(int x, int y,Mat imgThresholded2 )
{
	int posX=x;
	int posY=y;
	Mat imgOriginal11 =imgThresholded2;	
	int t= screen_width-screen_height; //840
	int z=image_width-image_height; //560
  	int temp_posX = posX;
  	int temp_posY = posY;
    	std::cout<<"Mouse X:"<<temp_posX<<"\t"<<"Mouse Y:"<<temp_posY<<endl;
  	XWarpPointer(dpy, None, root_window, 0, 0, 3, 0, temp_posX, temp_posY);
  	XFlush(dpy);
    	Point centerCircle1(posX, posY); 
  	int radiusCircle = 20;
  	Scalar colorCircle1(0,0,255);
  	int thicknessCircle1 = 5;
  	circle(imgOriginal, centerCircle1, radiusCircle, colorCircle1, thicknessCircle1);
      	return make_tuple(posX, posY, temp_posX, temp_posY);
  	
  	
}



	/** This function is used to calculate the moments 
*/
 tuple<int, int> VirtualPainter::moments1(Mat imgThresholded2)
 
 {
 	int posX=0;
 	int posY=0;
 	Moments oMoments = moments(imgThresholded2);
 	double dM01 = oMoments.m01;
  	double dM10 = oMoments.m10;
  	double dArea = oMoments.m00;
    	float m = (float)screen_height/(float)screen_width;
      
 	

  // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
      


 	image_width=imgTmp.cols;
 	image_height=imgTmp.rows;

        if (dArea > 10000)
  	{
    	 posX = dM10 / dArea;
    	 posY = dM01 / dArea; 
        if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   	{
   
  	if( posX >=1640 && posX<=1910 && posY>=500 && posY <=650)
  	{
  
  	int randNum1 = rand()%(max-min + 1) + min;
  	int randNum2 = rand()%(max-min + 1) + min;  	
  	int randNum3 = rand()%(max-min + 1) + min;  	
        int b = randNum1;  
        int g = randNum2;
        int r = randNum3;  	
        
        std::cout<<r<<"\t"<<g<<"\t"<<b<<std::endl;
  	
  	pen_color = {b,g,r};
  	
  	std::cout<<pen_color<<std::endl;
  	
  	}
  	
  	
  	
 // Eraser Operation
  	
  	
  	if (posX >=840 && posX<=1080 && posY>=935 && posY <=1070)
  	{
  	pen_color = {0,0,0};
  	
  	}
  	
  	
 // Clear Screen
   
   	if (posX >=840 && posX<=1080 && posY>=10 && posY <=135)
  	{
    	imgLines = Mat::zeros( Size(1920,1080), CV_8UC3 );;   
  	}
  	
 
 
 // Increase the thickness of brush
  	
  	if (posX >=10 && posX<=270 && posY>=270 && posY <=380)
  
  	{
  	if(thickness == thick_max)
  		{
  	thickness = thick_max;
  		}
  	else
  		{
  	thickness = thickness + 1; 
  		}
  	}
  
  
  
 // Decrease the thickness of brush 
 	 if (posX >=10 && posX<=270 && posY>=675 && posY <=785) 
     	 {
 	 //pen_color = {0,0,255};
 	 if(thickness == thick_min)
  		{
  	thickness = thick_max;
  		}
  	else
  		{
  	thickness = thickness - 1; 
  		}
 	 
  	  }  
 	 
 	 if(iLastX ==0 && iLastY==0)
 	 {
 	 line(imgLines, Point(posX, posY), Point(posX, posY),pen_color, thickness);
 	 }
 	 else
 	 {		
             	//Draw a red line from the previous point to the current point
    	line(imgLines, Point(posX, posY), Point(iLastX, iLastY),pen_color, thickness);
    	}
      	}
        iLastX= posX;
        iLastY = posY;
       
        }
  
        imgOriginal = imgOriginal + imgLines;

        return make_tuple(posX,posY);
 
}
 
  /** This function is doing Preprocessing like thresholding, erode and dilate
*/
Mat VirtualPainter:: pre_process1(Mat  imgHSV)
{
 	
 	int iLowH = 170;
	 int iHighH = 179;

 	int iLowS = 150; 
 	int iHighS = 255;

 	int iLowV = 60;
 	int iHighV = 255;
 
  	Mat imgThresholded;

  	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
      
  	//morphological opening (removes small objects from the foreground)

 	 erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

  	//morphological closing (removes small holes from the foreground)
  	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	return imgThresholded;


}

	/** This function is used to convert RGB TO HSV
*/

Mat VirtualPainter:: rgb_hsv(Mat  imgOriginal)
{
 
  	 Mat imgHSV;
  	 cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
 	 return imgHSV;
 }
   
   
   /** This function is used to capture the video from webcam
*/

int VirtualPainter:: processimage()
{
		VideoCapture cap(0); //capture the video from webcam
    		if ( !cap.isOpened() )  // if not success, exit program
    			{
         			cout << "Cannot open the web cam" << endl;
        			 return -1;
   			}

   		cap.read(imgTmp);
  		imgLines = Mat::zeros( Size(1920,1080), CV_8UC3 );;
  	 
    while (true)
    {
        
        namedWindow("Original", 0);
    	setWindowProperty("Original", 0, 1);
    	bool bSuccess = cap.read(imgOriginal); // read a new frame from video
         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }
     
        Size size(screen_width,screen_height);
        Mat dst;
        resize(imgOriginal,dst,size);
        imgOriginal= dst.clone();
        imgTmp = dst.clone();
   	
   	Mat imgThresholded1= rgb_hsv( imgOriginal);// Function to convert RGB to HSV 
   	Mat imgThresholded2 =pre_process1( imgThresholded1 ); // Function to  pre_processed image 
  	int x ,y; 
  	int posX, posY, temp_posX, temp_posY;

   	tie(x,y)=moments1(imgThresholded2);// calculate the moments  	
  	tie(posX, posY, temp_posX, temp_posY)= mousepointer( x,  y, imgThresholded2 );
  	
  	
	cv::rectangle( imgOriginal, cv::Point2f( 1640, 500 ), cv::Point2f(1910, 650), cv::Scalar( 255, 0, 0 ),-1 );
	string str1 = "Change_pencolor"; 
	cv::putText(imgOriginal,str1,cv::Point(1640,560),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,255,0),2,false);
	
	
	cv::rectangle( imgOriginal, cv::Point2f( 840, 935 ), cv::Point2f(1080, 1070), cv::Scalar( 255, 0, 0 ),-1 );
	string str2 = "Eraser"; 
	cv::putText(imgOriginal,str2,cv::Point(880,1000),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,255,0),2,false);

	
	
	cv::rectangle( imgOriginal, cv::Point2f( 840, 10 ), cv::Point2f(1080, 135), cv::Scalar( 255, 0, 0 ),-1 );
	string str3 = "Clear_screen"; 
	cv::putText(imgOriginal,str3,cv::Point(845,60),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,255,0),2,false);
	
	

   	cv::rectangle( imgOriginal, cv::Point2f( 10, 270 ), cv::Point2f(270, 380), cv::Scalar( 255, 0, 0 ),-1 );
	string str4 = "Thickness++"; 
	cv::putText(imgOriginal,str4,cv::Point(10,315),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,255,0),2,false);
	
	cv::rectangle( imgOriginal, cv::Point2f( 10, 675 ), cv::Point2f(270, 785), cv::Scalar( 255, 0, 0 ),-1 );
	string str5 = "Thickness--"; 
	cv::putText(imgOriginal,str5,cv::Point(10,740),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,255,0),2,false);
	
   	 imshow("Original", imgOriginal);
   	
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    
   
     }
        
     return 0;
            
 }
 
 
 
 
 
 
 
 

