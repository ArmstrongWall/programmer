#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iomanip>

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    cv::Mat Img = cv::imread("label.png", CV_LOAD_IMAGE_UNCHANGED);//CV_LOAD_IMAGE_GRAYSCALE   CV_LOAD_IMAGE_COLOR  CV_LOAD_IMAGE_UNCHANGED

    if(!Img.data)
    {
        cout<<"could not open"<<endl;
        return -1;
    }

    cout << Img.rows << " " << Img.cols << " " << Img.channels() << endl;

    cv::Mat d_Img = Img.clone();


    cout << d_Img.at<cv::Vec3b>(d_Img.rows-1,d_Img.cols-1);

    uchar* p = d_Img.data;
//    for(int i=0;i < d_Img.rows*d_Img.cols *d_Img.channels() ;++i)
//    {
//
//        //cout << (*d_Img.data);
//        *p = 129;
//        p = p+2;
////        for(int j=0; j< d_Img.cols *d_Img.channels() ;++j)
////        {
//            //d_Img.at<uchar>(i,j) = 128;
//
//
////            if(d_Img.at<cv::Vec3b>(i,j)[0]  == 6)
////                d_Img.at<cv::Vec3b>(i,j)=0;
////            else
//            //d_Img.at<uchar>(i,j) = 128;
////            if(d_Img.at<cv::Vec3b>(i,j/2)[0]  == 6)
////            {
////                cout << d_Img.at<cv::Vec3b>(i,j/2);
////                d_Img.at<uchar>(i,j/2) = 128;
////                d_Img.at<cv::Vec3b>(i,j)[1] = 64;
////                d_Img.at<cv::Vec3b>(i,j)[2] = 128;
////            }
//
//        //}
//    }

    imshow("src",Img);
    imshow("dst",d_Img);

    cv::waitKey(0);

    return 0;

}