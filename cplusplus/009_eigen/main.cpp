#include<iostream>
#include<vector>
#include <eigen3/Eigen/Dense>

using namespace std;
constexpr double DEG_TO_RAD = M_PI / 180.0;

int main(int argc , char ** argv)
{
    Eigen::Matrix3d max_33;
    //max_33 = Eigen::Matrix3d::Random();

    max_33 << 0,-3,2,3,0,-1,2,-1,0;
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
    double roll  = 0.1017971337 * DEG_TO_RAD;//x
    double pitch = -0.0213317815 * DEG_TO_RAD;//y
    double yaw   = (35.5819854736) * DEG_TO_RAD;//z

//从旋转轴初始化四元数
    Eigen::Quaterniond q =
            Eigen::AngleAxisd( yaw ,  Eigen::Vector3d::UnitZ()) *
            Eigen::AngleAxisd( roll,   Eigen::Vector3d::UnitX()) *
            Eigen::AngleAxisd( pitch , Eigen::Vector3d::UnitY());

    cout << "Quaternion1" << endl << q.coeffs() << endl;
    Eigen::Vector3d velocity(3.6,0,0);
    velocity = q*velocity;
    std::cout<< "velocity = "  << std::endl << velocity.transpose() << std::endl;


    Eigen::Matrix3d quater_to_matrix3 = q.matrix();
    Eigen::Vector3d  unreal_eulerAngles = quater_to_matrix3.eulerAngles(2,1,0);//z y x
    cout << "unreal roll pitch yaw " << unreal_eulerAngles.transpose()<<endl;


    Eigen::Matrix3d quater_to_matrix;
    quater_to_matrix = q.matrix();
    cout << "unreal Rotation_matrix1" << endl << quater_to_matrix << endl;


//直接初始化四元数
    Eigen::Quaterniond q2;
    q2.x()= 0.0467411237479;
    q2.y()= 0.000437485847171;
    q2.z()= -0.30571784276;
    q2.w()= -0.950974067246;

    Eigen::Matrix3d quater_to_matrix2;
    quater_to_matrix2 = q2.matrix();
    cout << "Apollo Rotation_matrix2" << endl << quater_to_matrix2 << endl;

    Eigen::Vector3d  Apollo_eulerAngles = quater_to_matrix2.eulerAngles(2,1,0);//z y x
    cout << "Apollo roll pitch yaw " << Apollo_eulerAngles.transpose()<<endl;




    return 0;
}