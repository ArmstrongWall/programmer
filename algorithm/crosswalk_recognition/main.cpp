#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iomanip>
#include <chrono>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace cv;
int w=752;
int h=480;

int main()
{

    vector<Vec4d> Lines; //含有4个int元素的向量,0,1元素是线段起点，2，3元素是线段终点

    String pattern = "/home/wzq/git/dataset/uisee/data/00_h0_5m/image_0/*.png";//s
    vector<String> fn;

    glob(pattern, fn, false);


    char* semanticMap = new char[w*h] ;


    size_t count = fn.size();
    for (size_t i = 0; i < count; i++)
    //for (size_t i = 0; i < 1; i++)
    {
        auto start = std::chrono::system_clock::now();
        memset(semanticMap,0,w*h*sizeof(char));

        Mat frame = imread(fn[i],IMREAD_GRAYSCALE);
//        Mat origin_frame = imread(fn[i],IMREAD_GRAYSCALE);
//        Eigen::Vector3f* dI = new Eigen::Vector3f[origin_frame.cols*origin_frame.rows*sizeof(Eigen::Vector3f)];
//
//
//        for(int i = 0; i < origin_frame.cols * origin_frame.rows; i++)
//            dI[i][0]  = static_cast<float> (origin_frame.data[i]);
//
//
//        Mat frame(origin_frame.rows, origin_frame.cols, CV_8UC1);
//
//        auto start = std::chrono::system_clock::now();
//
//        for(int i = 0; i < frame.cols * frame.rows; i++)
//            frame.data[i] = static_cast<uchar> (dI[i][0]);

        if (frame.empty()) {
            std::cout << "ERROR! blank frame grabbed" << std::endl;
            return false;
        }
        Mat roi = frame;
        threshold(roi, roi, 50, 255, CV_THRESH_BINARY);   //灰度变二值


        Mat CannyImg;
        Canny(frame, CannyImg, 50, 10, 3);//canny 算子 上下阈值越大，边缘就越少

        Mat DstImg = frame;
        HoughLinesP(CannyImg, Lines, 1, CV_PI / 360, 170,200,15);

        cvtColor(frame, DstImg, CV_GRAY2BGR);


        for (auto lines : Lines)
        {
            if(lines[0] != lines[2]) {
                for (auto x = static_cast<int>(lines[0]); x < lines[2]; x++) {
                    double k = (lines[1] - lines[3])/(lines[0] - lines[2]);
                    auto y =  static_cast<int>(k*(x - lines[2]) + (lines[3]));
                    semanticMap[x+y*frame.cols] = 100;
                    DstImg.at<Vec3b>(y,x)[0]=0;//set (y,x) is because Mirror flip
                    DstImg.at<Vec3b>(y,x)[1]=0;
                    DstImg.at<Vec3b>(y,x)[2]=255;
                }
            }
        }

//        //Mat semanticMap_frame(origin_frame.rows, origin_frame.cols, CV_8UC1);
//        Mat semanticMap_frame(frame.rows,frame.cols, CV_8UC1);
//
//        for(int i = 0; i < semanticMap_frame.cols * semanticMap_frame.rows; i++)
//            semanticMap_frame.data[i] = static_cast<uchar> (semanticMap[i]);
//
//        imshow("semanticMap_frame", semanticMap_frame);
        //imshow("HoughLines_Detect", CannyImg);
        imshow("HoughLines_Detect", DstImg);
        //imshow("HoughLines_Detect", roi);
        //imwrite(picture_name, DstImg);


        if(waitKey(1)==27)
            break;

        auto end   = std::chrono::system_clock::now();

        auto duration = std::chrono::duration_cast<chrono::microseconds>(end - start);

        std::cout<< duration.count()/1000000.00 <<std::endl;



    }

    delete[] semanticMap;





}



int pic2video()
{
    // 构造一个VideoWriter
    VideoWriter video("inputVideo.avi", CV_FOURCC('M', 'J', 'P', 'G'), 60.0, Size(w, h));
    // 从一个文件夹下读取多张jpg图片
    String pattern = "/home/wzq/git/dataset/uisee/data/00_h0_5m/image_0/*.png";
    vector<String> fn;

    glob(pattern, fn, false);

    size_t count = fn.size();
    for (size_t i = 0; i < count; i++)
    {
        Mat image = imread(fn[i]);
        // 这个大小与VideoWriter构造函数中的大小一致。
        resize(image, image, Size(w, h));
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
