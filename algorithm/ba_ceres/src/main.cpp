//#include<iostream>
//#include<ceres/ceres.h>
//
//

//
//int main(int argc, char** argv) {
//
//
//    google::InitGoogleLogging(argv[0]);
//
//    // 寻优参数x的初始值，为5
//    double initial_x = 5.0;
//    double x = initial_x;
//
//    // 第二部分：构建寻优问题
//    ceres::Problem problem;
//    ceres::CostFunction* cost_function =
//            new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
//    //使用自动求导，将之前的代价函数结构体传入，第一个1是输出维度，即残差的维度，第二个1是输入维度，即待寻优参数x的维度。
//    problem.AddResidualBlock(cost_function, NULL, &x); //向问题中添加误差项，本问题比较简单，添加一个就行。
//
//    //第三部分： 配置并运行求解器
//    ceres::Solver::Options options;
//    options.linear_solver_type = ceres::DENSE_QR; //配置增量方程的解法
//    options.minimizer_progress_to_stdout = true;//输出到cout
//    ceres::Solver::Summary summary;//优化信息
//    Solve(options, &problem, &summary);//求解!!!
//
//    std::cout << summary.BriefReport() << "\n";//输出优化的简要信息
//    //最终结果
//    std::cout << "x : " << initial_x
//              << " -> " << x << "\n";
//
//
//    return 0;
//}
//
//
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <ceres/ceres.h>
#include <chrono>

typedef Eigen::Matrix<double,3,3> Mat33;
typedef Eigen::Matrix<double,3,1> Vec3;

using namespace std;

struct CostFunctor {
    template <typename T>
    bool operator()(const T* const x, T* residual) const {
        residual[0] = T(10.0) - x[0];
        return true;
    }
};

// 代价函数的计算模型
struct CURVE_FITTING_COST
{
    CURVE_FITTING_COST ( double x, double y ) : _x ( x ), _y ( y ) {}
    // 残差的计算
    template <typename T>
    bool operator() (
            const T* const abc,     // 模型参数，有3维
            T* residual ) const     // 残差
    {
        residual[0] = T ( _y ) - ceres::exp ( abc[0]*T ( _x ) *T ( _x ) + abc[1]*T ( _x ) + abc[2] ); // y-exp(ax^2+bx+c)
        return true;
    }
    const double _x, _y;    // x,y数据
};

int main ( int argc, char** argv )
{
    double a=1.0, b=2.0, c=1.0;         // 真实参数值
    int N=100;                          // 数据点
    double w_sigma=1.0;                 // 噪声Sigma值
    cv::RNG rng;                        // OpenCV随机数产生器
    double   abc[3]   = {0.01,0.05,0.01};            // abc参数的估计值

    vector<double> x_data, y_data;      // 数据

    cout<<"generating data: "<<endl;
    for ( int i=0; i<N; i++ )
    {
        double x = i/100.0;
        x_data.push_back ( x );
        y_data.push_back (
                exp ( a*x*x + b*x + c ) + rng.gaussian ( w_sigma )
        );
        cout<<x_data[i]<<" "<<y_data[i]<<endl;
    }

    // 构建最小二乘问题
    ceres::Problem problem;


    // 配置求解器
    ceres::Solver::Options options;     // 这里有很多配置项可以填
    options.linear_solver_type = ceres::DENSE_QR;  // 增量方程如何求解
    options.minimizer_progress_to_stdout = false;   // 输出到cout
    //options.max_solver_time_in_seconds = 0.015;

    ceres::Solver::Summary summary;                // 优化信息
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    for ( int i=0; i<N; i++ )
    {
        problem.AddResidualBlock (     // 向问题中添加误差项
                // 使用自动求导，模板参数：误差类型，输出维度，输入维度，维数要与前面struct中一致
                new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3> (
                        new CURVE_FITTING_COST ( x_data[i], y_data[i] )
                ),
                nullptr,            // 核函数，这里不使用，为空
                abc                 // 待估计参数
        );
    }
    ceres::Solve ( options, &problem, &summary );  // 开始优化
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
    cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;

    // 输出结果
    cout<<summary.BriefReport() <<endl;
    cout<<"estimated a,b,c = ";
    for ( auto a:abc ) cout<<a<<" ";
    cout<<endl;
    double   state[3] = {0.01,0.05,0.01};            // abc参数的估计值


    Mat33    Hessian_cam        = Mat33::Zero();
    Vec3     b_cam              = Vec3::Zero();

    chrono::steady_clock::time_point t3 = chrono::steady_clock::now();

    for(int i = 0; i < x_data.size(); i++) {

        Vec3 jacobian;
        double y = ceres::exp ( x_data[i] * x_data[i] * state[0] + x_data[i] * state[1]  + state[2] );
        jacobian <<  y * x_data[i] * x_data[i], y * x_data[i] , y;
        double res      = y - y_data[i];


        Hessian_cam += jacobian *  jacobian.transpose();
        b_cam       += jacobian *  res;
    }

    for(int iteration = 0; iteration < 30; iteration++) {

        Vec3 inc = Vec3::Zero();
        inc = (Hessian_cam).llt().solve(-b_cam);
        Hessian_cam.setZero();
        b_cam.setZero();

        state[0] += inc[0];
        state[1] += inc[1];
        state[2] += inc[2];

        for(int i = 0; i < x_data.size(); i++) {

            Vec3 jacobian;
            double y = ceres::exp ( x_data[i] * x_data[i] * state[0] + x_data[i] * state[1]  + state[2] );
            jacobian <<  y * x_data[i] * x_data[i], y * x_data[i] , y;
            double res      = y - y_data[i];


            Hessian_cam += jacobian *  jacobian.transpose();
            b_cam       += jacobian *  res;
        }

//        if( inc.norm() < 1e-4 ) {
//            std::cout <<" \nir =  " << iteration << ", inc is too small, break!!! \n";
//            break;
//        }


    }
    chrono::steady_clock::time_point t4 = chrono::steady_clock::now();


    cout<<"estimated a,b,c = ";
    for ( auto a:state ) cout<<a<<" ";
    cout<<endl;

    chrono::duration<double> mytime_used = chrono::duration_cast<chrono::duration<double>>( t4-t3 );
    cout<<"my solver time cost = "<<mytime_used.count()<<" seconds. "<<endl;


    return 0;
}