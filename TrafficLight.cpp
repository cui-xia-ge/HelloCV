#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace cv;
#define minarea 20000

int editFrame(Mat &frame,Mat mask,std::string text)
{
    std::vector<Vec4i> h;
    std::vector<std::vector<Point>> contours;
    findContours(mask,contours,h,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for(int i=0;i<contours.size();i++)
    {
        int area=contourArea(contours[i]); 
        if(area>=minarea)
        {
            Rect find=boundingRect(contours[i]);
            rectangle(frame,find,Scalar(255,0,255),3);
            putText(frame,text,Point(10,50),FONT_HERSHEY_SIMPLEX,2,Scalar(0,255,255),2);
        }
    }
    return 0;
}
int main()
{
    VideoCapture cap("/home/cxg/Resources/TrafficLight.mp4");
    Mat frame,rmask,gmask,mask,fmHSV,fblur,rf;
    if(!cap.isOpened())
    {
        std::cout<<"readfailure\n";
        return 1;
    }
    Scalar rlower(175,110,55);
    Scalar rupper(179,230,255);
    Scalar glower(79,187,140);
    Scalar gupper(89,252,214);
    VideoWriter result("/home/cxg/Resources/result.avi",cv::VideoWriter::fourcc('X','2','6','4'),cap.get(CAP_PROP_FPS),Size(cap.get(CAP_PROP_FRAME_WIDTH),cap.get(CAP_PROP_FRAME_HEIGHT)));
    while(cap.read(frame))
    {
        cvtColor(frame,fmHSV,COLOR_BGR2HSV);
        inRange(fmHSV,rlower,rupper,rmask);
        inRange(fmHSV,glower,gupper,gmask);
        editFrame(frame,rmask,"RED");
        editFrame(frame,gmask,"GREEN");
        result.write(frame);
    }
    
    return 0;
}

   //debug code
    /* int hmin,smin,vmin,smax,hmax,vmax;
    namedWindow("Trackbars");
    createTrackbar("Hmin", "Trackbars", &hmin,179);
    createTrackbar("Hmax", "Trackbars", &hmax,179);
    createTrackbar("Smin", "Trackbars", &smin,255);  
    createTrackbar("Smax", "Trackbars", &smax,255);
    createTrackbar("Vmin", "Trackbars", &vmin,255);
    createTrackbar("Vmax", "Trackbars", &vmax,255);
    cap.read(frame); 
    while(cap.read(frame)){
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);
        resize(frame,rf,Size(),0.5,0.5);
        cvtColor(rf,fmHSV,COLOR_BGR2HSV);
        //inRange(fmHSV,lower,upper,mask);
        imshow("H",fmHSV);
        //imshow("mk",mask);
        if(waitKey(20)=='q')
            break;
    }
    cap.read(frame);
    while(1){
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);
        resize(frame,rf,Size(),0.5,0.5);
        cvtColor(rf,fmHSV,COLOR_BGR2HSV);
        inRange(fmHSV,lower,upper,mask);
        imshow("H",fmHSV);
        imshow("mk",mask);
        waitKey(5);
    }  */

    
