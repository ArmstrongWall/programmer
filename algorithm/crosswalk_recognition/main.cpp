#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iomanip>
#include <chrono>
#include <eigen3/Eigen/Dense>


using namespace cv;
using namespace std;

void getData(vector<int> &in, std::map<int,int> &out)
{
    for (int i = 0; i < in.size(); i++) {
        out.insert({i,in[i]});
    }
}


void findPeaks( std::map<int,int> &in,std::map<int,int> &out )
{
    const int NOISE = -1;               // Level up to and including which peaks will be excluded
    int grad = -1;                      // Sign of gradient (almost)
    //    =  1 for increasing
    //    =  0 for level AND PREVIOUSLY INCREASING (so potential wide peak)
    //    = -1 for decreasing OR level, but previously decreasing
    // A sharp peak is identified by grad=1 -> grad=-1
    // A wide  peak is identified by grad=0 -> grad=-1
    out.clear();
    auto map_it = in.begin();

    for ( ; map_it != in.end(); map_it++ ){
        auto map_it_next = (++map_it)--;
        if ( map_it_next->second < map_it->second ){        // Only possibility of a peak
            if ( grad == 1 && map_it->second > NOISE ){
                out.insert({map_it->first,map_it->second});
            }
            grad = -1;
        }
        else if ( map_it_next->second == map_it->second ){   // Check for start of a wide peak
                if ( grad == 1 ){
                    grad = 0;
                }
        }
        else{
            grad = 1;
        }
    }
    in.clear();
    for(auto x:out) {
        in.insert({x.first,x.second});
    }
}

class CHistogram {
protected:
    cv::Mat	bins;
public:
    CHistogram() :in(256,0.0f){ };
    ~CHistogram() { };
    virtual int calculate( cv::Mat &image ) = 0;
    virtual bool normalize( void ) = 0;
    virtual cv::Mat render( void ) = 0;

    std::vector<int> in;

};

class CHistogramGray : public CHistogram {
    void clear() {
        bins.setTo( Scalar( 0.f ) );
    };
public:
    CHistogramGray() {
        bins = Mat( 1, 256, CV_32F, Scalar( 0.f ) );
    }
    int calculate( Mat& image ) {
        if( image.channels() != 1 || image.type() != CV_8U ) { return 1; }
        this->clear();
        Mat_< uchar >::iterator it = image.begin< uchar >();
        Mat_< uchar >::iterator itend = image.end< uchar >();
        for( ; it != itend; ++it ) {
            bins.at< float >( 0, *it ) += 1.f;
            in[*it] += 1.f;
        }
        return 0;
    }
    bool normalize( void ) {
        Mat_< float >::iterator it = bins.begin< float >();
        Mat_< float >::iterator itend = bins.end< float >();
        float max = 1.f;
        for( ; it != itend; ++it ) {
            if( *it > max ) max = *it;
        }
        bins /= max;

        std::map<int,int> inmap;
        std::map<int,int> out;
        getData(in,inmap);

        int max_index = 0;
        int max_value = 0;
        auto map_it = inmap.begin();

        for ( ; map_it != inmap.end(); map_it++ )
        {
            if(map_it->second > max_value){
                max_value = map_it->second;
                max_index = map_it->first;
            }

        }
        int i = 0;
        while (true) {
            findPeaks(inmap,out);
            i++;
            if(inmap.size()<5)
                break;
        }

        if(inmap.find(max_index) == inmap.end()) {
            inmap.insert({max_index,max_value});
        }
        if(inmap.size() >= 2 && inmap.size() <= 3 ) {
            auto map_it1 = inmap.begin();
            auto map_it2 = (++map_it1)--;
            if( map_it1->second > map_it2->second && (map_it2->first- map_it1->first) > 40 ) {
                cout<<" FIND CROSS !!!!!!!! "<<endl<<endl<<endl;
                return true;
            }
        }

        return false;

    }
    Mat render( void ) {
        Mat result( 100, 256, CV_8U, Scalar( 0 ) );
        Point start( 0, 0 ), end( 0, 0 );
        for( int i = 0; i < 256; i++ ) {
            start.x = end.x = i;
            end.y = cvRound( 100.f * bins.at< float >( i ) );
            line( result, start, end, Scalar( 192 ) );
        }
        flip( result, result, 0 );

        return result;
    }
};

int w=640;
int h=480;

void hist_find_crosswalk(Mat &frame,Mat &ui_img){
    int interval = 80;

    for (int b = 320; b < h; b+=interval)
        for (int a = 0; a < w; a+=interval)
        {
            Mat seg(interval, interval, CV_8UC1);
            for (int y = b; y < b+interval; y++)for (int x = a; x < a+interval; x++)
                {

                    if(x >= w||y >= h) {
                        continue;
                    }

                    seg.data[x-a+(y-b)*interval]=frame.data[x+y*w];

                    if(y == b || x == a) {
                        ui_img.at<Vec3b>(y,x)[0]=0;//set (y,x) is because Mirror flip
                        ui_img.at<Vec3b>(y,x)[1]=0;
                        ui_img.at<Vec3b>(y,x)[2]=255;
                    }
                }
            imshow( "seg", seg );
            imwrite("seg/"+std::to_string(a)+"@"+std::to_string(b)+".jpg",seg);

            CHistogramGray histogram;
            if( histogram.calculate (seg) == 0 ) {
                if(histogram.normalize ()) {
                    for (int y = b; y < b+interval; y++)for (int x = a; x < a+interval; x++)
                        {
                            {
                                ui_img.at<Vec3b>(y,x)[0]=0;//set (y,x) is because Mirror flip
                                ui_img.at<Vec3b>(y,x)[1]=0;
                                ui_img.at<Vec3b>(y,x)[2]=255;
                            }

                        }
                }
                Mat display = histogram.render ();
                namedWindow( "Histogram" );
                imshow( "Histogram", display );
                imwrite("hist/"+std::to_string(a)+"@"+std::to_string(b)+".jpg",display);

                //while(waitKey(2)!=27){};

            }
        }
}

int main()
{

    vector<Vec4d> Lines; //含有4个int元素的向量,0,1元素是线段起点，2，3元素是线段终点

    //String pattern = "/home/wzq/git/programmer/algorithm/crosswalk_recognition/cmake-build-debug/seg/520@0.jpg";//s
//    String pattern = "/home/wzq/git/dataset/uisee/data/00_h1m/image_0/0000000460.png";//s
    String pattern = "/home/wzq/git/dataset/uisee/data/00_h1m/image_0/*.png";//s
    vector<String> fn;

    glob(pattern, fn, false);

    char* semanticMap = new char[w*h] ;

    size_t count = fn.size();
    for (size_t i = 0; i < count; i++)
        //for (size_t i = 0; i < 1; i++)
    {
        auto start = std::chrono::system_clock::now();
        memset(semanticMap,0,w*h*sizeof(char));

        Mat ori = imread(fn[i],IMREAD_GRAYSCALE);
        //imshow("ori", ori);

        Mat resize_frame(h, w, CV_8UC1);

        resize(ori,resize_frame, Size(w,h));

        Mat frame = resize_frame(Rect(0,320,w,160));

        imshow( "roi", frame );

        Mat CannyImg;
        Canny(frame, CannyImg, 50, 10, 3);//canny 算子 上下阈值越大，边缘就越少

        Mat DstImg = frame;
        HoughLinesP(CannyImg, Lines, 1, CV_PI / 360, 170,100,15);

        cvtColor(frame, DstImg, CV_GRAY2BGR);

        hist_find_crosswalk(frame,DstImg);
        for (auto lines : Lines)
        {
            if(lines[0] != lines[2]) {
                for (auto x = static_cast<int>(lines[0]); x < lines[2]; x++) {
                    double k = (lines[1] - lines[3])/(lines[0] - lines[2]);
                    auto y =  static_cast<int>(k*(x - lines[2]) + (lines[3]));
                    semanticMap[x+(y+320)*frame.cols] = 100;
                    DstImg.at<Vec3b>(y,x)[0]=0;//set (y,x) is because Mirror flip
                    DstImg.at<Vec3b>(y,x)[1]=0;
                    DstImg.at<Vec3b>(y,x)[2]=255;
                }
            }
        }
        Mat semanticMap_frame(resize_frame.rows,resize_frame.cols, CV_8UC1);

        for(int i = 0; i < semanticMap_frame.cols * semanticMap_frame.rows; i++)
            semanticMap_frame.data[i] = static_cast<uchar> (semanticMap[i]);

        imshow("semanticMap_frame", semanticMap_frame);
        //imshow("HoughLines_Detect", CannyImg);
        imshow("HoughLines_Detect", DstImg);
        //imshow("HoughLines_Detect", roi);
        //imwrite(picture_name, DstImg);
        if(waitKey(2)==27)
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

