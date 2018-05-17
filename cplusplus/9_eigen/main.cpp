#include<iostream>
#include<vector>
#include <eigen3/Eigen/Dense>

using namespace std;


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



    return 0;
}