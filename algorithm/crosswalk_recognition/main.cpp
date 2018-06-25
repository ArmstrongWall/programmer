#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iomanip>

using namespace std;
using namespace cv;

int main()
{
    vector<Vec4i> Lines; //含有4个int元素的向量,0,1元素是线段起点，2，3元素是线段终点

    String pattern = "/home/wzq/git/dataset/uisee/data/00_h0_5m/image_0/*.png";//s
    vector<String> fn;

    glob(pattern, fn, false);

    size_t count = fn.size();
    for (size_t i = 0; i < count; i++)
    {
        Mat frame = imread(fn[i]);
        // 这个大小与VideoWriter构造函数中的大小一致。
        //Mat frame = imread("0.png");
        if (frame.empty()) {
            std::cout << "ERROR! blank frame grabbed" << std::endl;
            return false;
        }
        Mat gray_frame;
        cvtColor(frame, gray_frame, CV_BGR2GRAY);

        Mat roi = gray_frame;
        threshold(roi, roi, 50, 255, CV_THRESH_BINARY);   //灰度变二值

        Mat CannyImg;
        Canny(gray_frame, CannyImg, 50, 10, 3);//canny 算子 上下阈值越大，边缘就越少

        Mat DstImg = frame;
        //cvtColor(frame, DstImg, CV_GRAY2BGR);

        HoughLinesP(CannyImg, Lines, 1, CV_PI / 360, 170,300,15);
        for (size_t i = 0; i < Lines.size(); i++)
        {
            line(DstImg, Point(Lines[i][0], Lines[i][1]), Point(Lines[i][2], Lines[i][3]), Scalar(0,0,255), 2, 8);
        }

        //imshow("HoughLines_Detect", CannyImg);
        imshow("HoughLines_Detect", DstImg);
        //imshow("HoughLines_Detect", roi);

////imwrite(picture_name, DstImg);
       if(waitKey(1)==27)
           break;

    }






}



int pic2video()
{
    // 构造一个VideoWriter
    VideoWriter video("inputVideo.avi", CV_FOURCC('M', 'J', 'P', 'G'), 60.0, Size(752, 480));
    // 从一个文件夹下读取多张jpg图片
    String pattern = "/home/wzq/git/dataset/uisee/data/00_h0_5m/image_0/*.png";
    vector<String> fn;

    glob(pattern, fn, false);

    size_t count = fn.size();
    for (size_t i = 0; i < count; i++)
    {
        Mat image = imread(fn[i]);
        // 这个大小与VideoWriter构造函数中的大小一致。
        resize(image, image, Size(752, 480));
        // 流操作符，把图片传入视频
        video << image;
    }
    cout << "处理完毕！" << endl;
    // 处理完之后会在得到一个名为test.avi的视频文件。
}


//
//using namespace std;
//
//int main() {
//    cout << "Hello, World!" << endl;
//
//    cv::Mat Img = cv::imread("000000.png", CV_LOAD_IMAGE_UNCHANGED);//CV_LOAD_IMAGE_GRAYSCALE   CV_LOAD_IMAGE_COLOR  CV_LOAD_IMAGE_UNCHANGED
//
//    if(!Img.data)
//    {
//        cout<<"could not open"<<endl;
//        return -1;
//    }
//
//    cout << Img.rows << " " << Img.cols << " " << Img.channels() << endl;
//
//    cv::Mat d_Img = Img.clone();
//
//
//    uchar* p = d_Img.data;
//    for(int i=0;i < d_Img.rows*d_Img.cols *d_Img.channels() ;++i)
//    {
//
//        printf("num %d is %d \n",i,*p);
//        p++;
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
//
//    //imshow("src",Img);
//    //imshow("dst",d_Img);
//
//    cv::waitKey(0);
//
//    return 0;
//
//}
