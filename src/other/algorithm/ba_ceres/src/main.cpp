#include "ceres/ceres.h"
#include <opencv2/core/core.hpp>
using namespace std;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;

class LocalParameterizationSE3 : public ceres::LocalParameterization {
public:
    virtual ~LocalParameterizationSE3() {}

    // SE3 plus operation for Ceres
    //
    //  T * exp(x)
    //
    virtual bool Plus(double const* T_raw, double const* delta_raw,
                      double* T_plus_delta_raw) const {

        T_plus_delta_raw[0] = T_raw[0] + delta_raw[0];
        T_plus_delta_raw[1] = T_raw[1] + delta_raw[1];

//        std::cout << "T_raw "             <<std::endl << T_raw[0] <<"," << T_raw[1] << std::endl<< std::endl;
//        std::cout << "delta_raw "         <<std::endl << delta_raw[0] <<"," << delta_raw[1] << std::endl<< std::endl;
//        std::cout << "T_plus_delta_raw "  <<std::endl << T_plus_delta_raw[0] <<"," << T_plus_delta_raw[1] << std::endl<< std::endl;

        return true;
    }

    // Jacobian of SE3 plus operation for Ceres
    //
    // Dx T * exp(x)  with  x=0
    //
    virtual bool ComputeJacobian(double const* T_raw,
                                 double* jacobian_raw) const {
        jacobian_raw[0] = 1;
        jacobian_raw[1] = 0;
        jacobian_raw[2] = 0;
        jacobian_raw[3] = 1;

        std::cout << "x=0, need  ComputeJacobian"  <<std::endl;

        return true;
    }

    virtual int GlobalSize() const { return 2; }
    virtual int LocalSize() const { return 2; }
};

class AnalyticCostFunctor : public ceres::SizedCostFunction<1,2> {
public:
    AnalyticCostFunctor(const double x, const double y) : x_(x), y_(y) {}
    virtual ~AnalyticCostFunctor() {}
    virtual bool Evaluate(double const* const* parameters,
                          double* residuals,
                          double** jacobians) const {
        const double a = parameters[0][0];
        const double b = parameters[0][1];

        residuals[0] = (a*x_+b)-y_;

        if (!jacobians) return true;
        double* jacobian = jacobians[0];
        if (!jacobian) return true;

        std::cout << "AnalyticCostFunctor  ComputeJacobian"  <<std::endl;


        jacobian[0] = x_;
        jacobian[1] = 1.0;
        return true;
    }

private:
    const double x_;
    const double y_;
};


int main(int argc, char** argv)
{

    double a=1.0, b=2.0;         // 真实参数值
    int N=20;                          // 数据点
    double w_sigma=0.1;                 // 噪声Sigma值
    cv::RNG rng;                        // OpenCV随机数产生器
    double ab[2] = {0.0,0.0};            // abc参数的估计值

    vector<double> x_data, y_data;      // 数据
    cout<<"generating data: "<<endl;
    for ( int i=0; i<N; i++ )
    {
        double x = i/100.0;
        x_data.push_back ( x );
        y_data.push_back (a*x + b + rng.gaussian ( w_sigma ));
        cout<<x_data[i]<<" "<<y_data[i]<<endl;
    }
    // Build the problem.
    Problem problem;

    problem.AddParameterBlock(
            ab,
            2,
            new LocalParameterizationSE3);

    for ( int i=0; i<N; i++ )
    {
        CostFunction* cost_function =new AnalyticCostFunctor( x_data[i], y_data[i] );
        problem.AddResidualBlock(cost_function, NULL, ab);
    }

    // Run the solver!
    Solver::Options options;
    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";
    std::cout << "output a: " << ab[0] << "\n"
              << "output b: " << ab[1] << "\n";
    return 0;
}

//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <ceres/ceres.h>
//#include <chrono>
//
//typedef Eigen::Matrix<double,3,3> Mat33;
//typedef Eigen::Matrix<double,3,1> Vec3;
//
//using namespace std;
//
//struct CostFunctor {
//    template <typename T>
//    bool operator()(const T* const x, T* residual) const {
//        residual[0] = T(10.0) - x[0];
//        return true;
//    }
//};
//
//// 代价函数的计算模型
//struct CURVE_FITTING_COST
//{
//    CURVE_FITTING_COST ( double x, double y ) : _x ( x ), _y ( y ) {}
//    // 残差的计算
//    template <typename T>
//    bool operator() (
//            const T* const abc,     // 模型参数，有3维
//            T* residual ) const     // 残差
//    {
//        residual[0] = T ( _y ) - ceres::exp ( abc[0]*T ( _x ) *T ( _x ) + abc[1]*T ( _x ) + abc[2] ); // y-exp(ax^2+bx+c)
//        return true;
//    }
//    const double _x, _y;    // x,y数据
//};
//
//int main ( int argc, char** argv )
//{
//    double a=1.0, b=2.0, c=1.0;         // 真实参数值
//    int N=100;                          // 数据点
//    double w_sigma=1.0;                 // 噪声Sigma值
//    cv::RNG rng;                        // OpenCV随机数产生器
//    double   abc[3]   = {0.01,0.05,0.01};            // abc参数的估计值
//
//    vector<double> x_data, y_data;      // 数据
//
//    cout<<"generating data: "<<endl;
//    for ( int i=0; i<N; i++ )
//    {
//        double x = i/100.0;
//        x_data.push_back ( x );
//        y_data.push_back (
//                exp ( a*x*x + b*x + c ) + rng.gaussian ( w_sigma )
//        );
//        cout<<x_data[i]<<" "<<y_data[i]<<endl;
//    }
//
//    // 构建最小二乘问题
//    ceres::Problem problem;
//
//
//    // 配置求解器
//    ceres::Solver::Options options;     // 这里有很多配置项可以填
//    options.linear_solver_type = ceres::DENSE_QR;  // 增量方程如何求解
//    options.minimizer_progress_to_stdout = false;   // 输出到cout
//    //options.max_solver_time_in_seconds = 0.015;
//
//    ceres::Solver::Summary summary;                // 优化信息
//    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
//
//    for ( int i=0; i<N; i++ )
//    {
//        problem.AddResidualBlock (     // 向问题中添加误差项
//                // 使用自动求导，模板参数：误差类型，输出维度，输入维度，维数要与前面struct中一致
//                new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3> (
//                        new CURVE_FITTING_COST ( x_data[i], y_data[i] )
//                ),
//                nullptr,            // 核函数，这里不使用，为空
//                abc                 // 待估计参数
//        );
//    }
//    ceres::Solve ( options, &problem, &summary );  // 开始优化
//    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
//    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>( t2-t1 );
//    cout<<"solve time cost = "<<time_used.count()<<" seconds. "<<endl;
//
//    // 输出结果
//    cout<<summary.BriefReport() <<endl;
//    cout<<"estimated a,b,c = ";
//    for ( auto a:abc ) cout<<a<<" ";
//    cout<<endl;
//
//
//
//    double   state[3] = {0.01,0.05,0.01};            // abc参数的估计值
//
//
//    Mat33    Hessian_cam        = Mat33::Zero();
//    Vec3     b_cam              = Vec3::Zero();
//
//    chrono::steady_clock::time_point t3 = chrono::steady_clock::now();
//
//    for(int i = 0; i < x_data.size(); i++) {
//
//        Vec3 jacobian;
//        double y = ceres::exp ( x_data[i] * x_data[i] * state[0] + x_data[i] * state[1]  + state[2] );
//        jacobian <<  y * x_data[i] * x_data[i], y * x_data[i] , y;
//        double res      = y - y_data[i];
//
//
//        Hessian_cam += jacobian *  jacobian.transpose();
//        b_cam       += jacobian *  res;
//    }
//
//    for(int iteration = 0; iteration < 30; iteration++) {
//
//        Vec3 inc = Vec3::Zero();
//        inc = (Hessian_cam).llt().solve(-b_cam);
//        Hessian_cam.setZero();
//        b_cam.setZero();
//
//        state[0] += inc[0];
//        state[1] += inc[1];
//        state[2] += inc[2];
//
//        for(int i = 0; i < x_data.size(); i++) {
//
//            Vec3 jacobian;
//            double y = ceres::exp ( x_data[i] * x_data[i] * state[0] + x_data[i] * state[1]  + state[2] );
//            jacobian <<  y * x_data[i] * x_data[i], y * x_data[i] , y;
//            double res      = y - y_data[i];
//
//
//            Hessian_cam += jacobian *  jacobian.transpose();
//            b_cam       += jacobian *  res;
//        }
//
////        if( inc.norm() < 1e-4 ) {
////            std::cout <<" \nir =  " << iteration << ", inc is too small, break!!! \n";
////            break;
////        }
//
//
//    }
//    chrono::steady_clock::time_point t4 = chrono::steady_clock::now();
//
//
//    cout<<"estimated a,b,c = ";
//    for ( auto a:state ) cout<<a<<" ";
//    cout<<endl;
//
//    chrono::duration<double> mytime_used = chrono::duration_cast<chrono::duration<double>>( t4-t3 );
//    cout<<"my solver time cost = "<<mytime_used.count()<<" seconds. "<<endl;
//
//
//    return 0;
//}