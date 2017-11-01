#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

int main(int argc,char** argv)
{
    
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2,Eigen::Vector3d(0,0,1)).toRotationMatrix();
    //构造一个沿着Ｚ轴旋转９０度的旋转向量，转化为旋转矩阵
    
    Sophus::SO3 SO3_R(R);
    //直接从旋转矩阵构造一个ＳＯ（３）
    cout << "SO(3) from Matrix:" << endl << SO3_R << endl;
    
    
    Sophus::SO3 SO3_v(0,0,M_PI/2);
    //直接从旋转向量构造
    cout << "SO(3) from Vector:" << endl << SO3_v << endl;
    
    Eigen::Quaterniond q(R);
    //从旋转矩阵构造四元数
    Sophus::SO3 SO3_q(q);
    //从四元数构造SO(3)
    cout << "SO(3) from Quaterniond:" << endl << SO3_q << endl;
    
    
    
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "so3 slef is" << endl << so3.transpose() << endl;
    //so3本身　
    
    cout << "so3^ " << endl << Sophus::SO3::hat(so3) << endl;
    //反对称矩阵
    
    
    
    
   
    return 0;
}

