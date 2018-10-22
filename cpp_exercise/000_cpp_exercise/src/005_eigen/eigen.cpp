//
// Created by wzq on 18-10-17.
//

#include "eigen.h"

#include<iostream>
#include<vector>
#include <eigen3/Eigen/Dense>

using namespace std;
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;

int eigen_demo( )
{

    double matrix_state_ = -0.09;
    Eigen::MatrixXd matrix_k_(1,4);
    matrix_k_<< 0.008,0,0.1,0.0014;
    cout << matrix_k_ * matrix_state_ <<endl;

    const double steer_angle_feedback = -(matrix_k_ * matrix_state_)(0, 0) * 180 /
                                        M_PI * 16 /
                                        470 * 100;
    cout << steer_angle_feedback <<endl;

    Eigen::Matrix3d max_33;
    //max_33 = Eigen::Matrix3d::Random();


    max_33 << 5,-3,2,3,0,-1,2,-1,0;

    cout << max_33(0,0) <<endl;
    cout << max_33 <<endl;
    cout << max_33.determinant() << endl;

    cout << "UnitZ is " << endl <<Eigen::Vector3d::UnitZ() << endl;

    //定义一个旋转轴
    Eigen::AngleAxisd t_V(M_PI / 4, Eigen::Vector3d(0, 0, 1));

    //1.使用旋转的角度和旋转轴向量（此向量为单位向量）来初始化角轴
    Eigen::AngleAxisd V1(M_PI / 4, Eigen::Vector3d(0, 0, 1));
    //以（0,0,1）为旋转轴，旋转45度
    cout << "Rotation_vector1" << endl << V1.matrix() << endl;

    //1.使用旋转的角度和旋转轴向量（此向量为单位向量）来初始化四元数,即使用q=[cos(A/2),n_x*sin(A/2),n_y*sin(A/2),n_z*sin(A/2)]
    Eigen::Quaterniond Q1(cos((M_PI / 4) / 2), 0 * sin((M_PI / 4) / 2), 0 * sin((M_PI / 4) / 2), 1 * sin((M_PI / 4) / 2));//以（0,0,1）为旋转轴，旋转45度
    //第一种输出四元数的方式,顺序是（x,y,z,w）
    cout << "Quaternion1" << endl << Q1.coeffs() << endl;

    Eigen::Vector3d v(1,0,0);
    cout<< "rotated"  << endl<< Q1*v.transpose() <<endl;


    //验证互为相反数的两组四元数表示同一个旋转
    double roll  = 0.000000 * DEG_TO_RAD;//x
    double pitch = 8.000000 * DEG_TO_RAD;//y
    double yaw   = 0.000000 * DEG_TO_RAD;//z


//从旋转轴初始化四元数
    Eigen::Quaterniond q =
            Eigen::AngleAxisd( pitch , Eigen::Vector3d::UnitY()) *
            Eigen::AngleAxisd( yaw ,  Eigen::Vector3d::UnitZ()) *
            Eigen::AngleAxisd( roll,   Eigen::Vector3d::UnitX()) ;

    cout << "q" << endl << q.coeffs() << endl;

    Eigen::Vector3d velocity(3.6,0,0);
    velocity = q*velocity;
    std::cout<< "velocity = "  << std::endl << velocity.transpose() << std::endl;


    Eigen::Matrix3d quater_to_matrix3 = q.matrix();
    Eigen::Vector3d  unreal_eulerAngles = quater_to_matrix3.eulerAngles(2,1,0);//z y x
    cout << "unreal roll pitch yaw " << unreal_eulerAngles.transpose()<<endl;


    Eigen::Matrix3d quater_to_matrix;
    quater_to_matrix = q.matrix();
    cout << "unreal Rotation_matrix1" << endl << quater_to_matrix << endl;

//验证互为相反数的两组四元数表示同一个旋转
    double roll1  = 0.53843 * DEG_TO_RAD;//x
    double pitch1 = 0.0 * DEG_TO_RAD;//y
    double yaw1   = 0.0 * DEG_TO_RAD;//z


//从旋转轴初始化四元数
    Eigen::Quaterniond q3 =
                            Eigen::AngleAxisd( roll1,   Eigen::Vector3d::UnitX())*
                            Eigen::AngleAxisd( pitch1 , Eigen::Vector3d::UnitY())*
                            Eigen::AngleAxisd( yaw1 ,  Eigen::Vector3d::UnitZ());

    cout << "q3" << endl << q3.coeffs() << endl;

    Eigen::Matrix3d quater_to_matrix4;
    quater_to_matrix4 = q3.toRotationMatrix();

    cout << "quater_to_matrix4 = " << endl << quater_to_matrix4 << endl;

    Eigen::Vector3d gravity(0,0,1);


    cout << "gravity = " << endl << quater_to_matrix4 * gravity << endl;

//直接初始化四元数
    Eigen::Quaterniond q2;
    q2.x()= -0.000680014;
    q2.y()= -0.073824;
    q2.z()=  0.00224139;
    q2.w()= -0.997269;

    Eigen::Matrix3d quater_to_matrix2;
    quater_to_matrix2 = q2.matrix();
    cout << "Apollo Rotation_matrix2" << endl << quater_to_matrix2 << endl;

    Eigen::Vector3d  Apollo_eulerAngles = quater_to_matrix2.eulerAngles(1,2,0);
    //eulerAngles(0,1,2),"2" represents the z axis and "0" the x axis
    cout << "Apollo y z x " << Apollo_eulerAngles.transpose()* RAD_TO_DEG<<endl;


    Eigen::Matrix3d K;
    K <<    -1, 2, 2,
            3,-1, 1,
            2, 2,-1;
    Eigen::EigenSolver<Eigen::Matrix3d> es(K);
    Eigen::MatrixXcd evecs = es.eigenvectors();//获取矩阵特征向量4*4，这里定义的MatrixXcd必须有c，表示获得的是complex复数矩阵
    Eigen::MatrixXcd evals = es.eigenvalues();//获取矩阵特征值 4*1
    Eigen::MatrixXd evalsReal;//注意这里定义的MatrixXd里没有c
    evalsReal=evals.real();   //获取特征值实数部分
    Eigen::MatrixXf::Index evalsMax;


    evalsReal.rowwise().sum().maxCoeff(&evalsMax);//得到最大特征值的位置
    Eigen::Vector3d q_eigen;
    q_eigen << evecs.real()(0, evalsMax), evecs.real()(1, evalsMax), evecs.real()(2, evalsMax);//得到对应特征向量

    std::cout << "evecs = "<< std::endl  <<  evecs << std::endl;
    std::cout << "evals = "<< std::endl  <<  evals << std::endl;

    return 0;
}