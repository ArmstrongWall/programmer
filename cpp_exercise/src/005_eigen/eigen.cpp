//
// Created by wzq on 18-10-17.
//

#include "eigen.h"

#include <iostream>
#include <vector>
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
#include <eigen3/Eigen/Dense>

using namespace std;
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;
typedef Eigen::Matrix<double,4,6> Mat46;
typedef Eigen::Matrix<double,3,9> Mat39;
typedef Eigen::Matrix<double,9,9> Mat99;
typedef Sophus::SO3<float> SO3f;
typedef Sophus::SO3<double> SO3;

typedef Sophus::SE3<float>  SE3f;
typedef Sophus::SE3<double> SE3;
typedef Eigen::Matrix<double,6,1> Vec6;


int eigen_block() {
    Eigen::Vector4d x;
    x.segment<2>(2) << 2,2;
    cout << "x \n" << x <<endl;


    Mat99    A = Mat99::Zero();
    A.block<3,3>(0,0)          =  Eigen::Matrix<double,3,3>::Ones();
    A.block<3,3>(3,0)          =  Eigen::Matrix<double,3,3>::Ones();       // P(i+1 : i+rows, j+1 : j+cols)
    A.block<3,3>(0,3)          =  Eigen::Matrix<double,3,3>::Ones() * 2;       // P(i+1 : i+rows, j+1 : j+cols)
    A.block<3,3>(3,3)          =  Eigen::Matrix<double,3,3>::Identity();
    A.block<3,3>(6,0)          =  Eigen::Matrix<double,3,3>::Ones();
    A.block<3,3>(6,3)          =  Eigen::Matrix<double,3,3>::Identity();
    A.block<3,3>(6,6)          =  Eigen::Matrix<double,3,3>::Ones();


    cout << "A \n" << A <<endl;


    Mat46              partial_point_xi  = Mat46::Zero();

    partial_point_xi.topLeftCorner(3,3)  = Eigen::Matrix<double,3,3>::Zero();
    partial_point_xi.topRightCorner(3,3) = Eigen::Matrix<double,3,3>::Identity();

    cout << "partial \n" << partial_point_xi<<endl;

    Mat39 Jacobian ;
    Jacobian.leftCols(3)       = Eigen::Matrix<double,3,3>::Zero();
    Jacobian.middleCols(3,3)   = Eigen::Matrix<double,3,3>::Identity();
    Jacobian.rightCols(3)      = Eigen::Matrix<double,3,3>::Zero();

    cout << "Jacobian \n" << Jacobian << "\n\n" <<endl;
}

int eigen_demo() {



    Eigen::Matrix<double,4,4>   imu_to_left_trans;
    imu_to_left_trans <<
                      0.99996651999999997,   0.00430873000000000,    0.00695718000000000,   -0.04777362000000000108,
            0.00434878000000000,  -0.99997400999999997,   -0.00575128000000000,   -0.00223730999999999991,
            0.00693222000000000,   0.00578135000000000,   -0.99995926000000002,   -0.00160071000000000008,
            0.0,                   0.0,                    0.0,                   1.0;

    std::cout << "point trans\n " << imu_to_left_trans.inverse()  << std::endl;


    Eigen::Matrix<double,4,4> cam_to_imu ;
    cam_to_imu <<
               0.0148655429818, -0.999880929698,   0.00414029679422, -0.0216401454975,
            0.999557249008,   0.0149672133247,  0.025715529948,   -0.064676986768,
            -0.0257744366974, 0.00375618835797, 0.999660727178,    0.00981073058949,
            0.0,              0.0,              0.0,               1.0;

    Eigen::Vector4d point(15,-1,30,1);

    std::cout << "point trans\n " << cam_to_imu * point<< std::endl;


//    Eigen::Vector3d  eulerAngles = cam_imu.eulerAngles(2,1,0);//eular angle z-y-x sequence
//    std::cout << "eular z-y-x " << eulerAngles.transpose() * RAD_TO_DEG << std::endl;



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
    Eigen::AngleAxisd V1(M_PI / 4, Eigen::Vector3d(0, 1, 0));
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


    Eigen::Vector3d a(1,1,1);
    Eigen::Vector3d b(3,3,3);

    std::cout << "c = " << (a-b).squaredNorm() << std::endl;

    //验证互为相反数的两组四元数表示同一个旋转
    double roll2  = 90.0 * DEG_TO_RAD;//x
    double pitch2 = 90.0 * DEG_TO_RAD;//y
    double yaw2   = 90.0 * DEG_TO_RAD;//z


//从旋转轴初始化四元数
    Eigen::Quaterniond q4 =
            Eigen::AngleAxisd( roll2,   Eigen::Vector3d::UnitX())*
            Eigen::AngleAxisd( pitch2 , Eigen::Vector3d::UnitY())*
            Eigen::AngleAxisd( yaw2 ,  Eigen::Vector3d::UnitZ());


    Eigen::Matrix3d quatertomatrix;
    quatertomatrix = q3.toRotationMatrix();

    Eigen::Vector3d vins(1.123792,-1.542760,0.377206);

    std::cout << "vins trans\n " << quatertomatrix * vins<< std::endl;

    //vins,+1.123792,-1.542760,+0.377206,gt,+0.432822,+2.284217,+0.319762




    return 0;
}
int Sophus_demo() {

//    Eigen::Vector3d deg(-0.00014365,0.01394026,-0.00082318);
//    SO3 a = SO3::exp(deg);
//    std::cout << "a = \n"<< a.matrix() << std::endl;

    float delta_time = 0.5;

    double omega[8] = {0, M_PI/16, M_PI/8, 3*M_PI/16, M_PI/4, 3*M_PI/16, M_PI/8, M_PI/16};

    double acc_x[8] = {0, 0.5, 1, 0.5, 0, -0.50, -1, -0.50};

    Eigen::Vector3d v_w(0,0,0);
    double g_norm = 9.8;
    Eigen::Vector3d gravity(0,g_norm,0);


    SO3   R_wb = SO3();
    for(int i = 0; i < 8; i++) {

        Eigen::Vector3d w(0,-omega[i],0);
        Eigen::Vector3d acc(acc_x[i],0,0);
        Eigen::Vector3d acc_body;
        acc_body = acc - gravity;

        R_wb = R_wb * SO3::exp(w*delta_time);

        v_w = v_w + SO3::exp(w*delta_time) * acc_body * delta_time + gravity * delta_time;

        Eigen::Matrix3d quater_to_matrix3 = R_wb.matrix();
        Eigen::Vector3d  unreal_eulerAngles = quater_to_matrix3.eulerAngles(1,0,2);//y-x-z
        cout <<"time " << i << ",eular y-x-z " << unreal_eulerAngles.transpose() * RAD_TO_DEG<<endl;
        cout << "v_w is\n" << v_w <<endl<<endl;

    }

    // 最后，演示一下更新
    Vec6 update_se3; //更新量
    update_se3.setZero();
    update_se3(0,0) = 1e-4d;
    SE3 SE3_updated = SE3()*SE3::exp(update_se3);
    cout<<"SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;

    update_se3(0,0) = -1e-4d;
    SE3_updated = SE3_updated*SE3::exp(update_se3);
    cout<<"again SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;


}

