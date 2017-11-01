#include<iostream>
#include<vector>
#include <Eigen/Dense>

using namespace std;

class A
{
public:
  virtual void play(){std::cout<<"A"<<std::endl;}
};

class B : public A
{
public:
  void play(){std::cout<<"B"<<std::endl;}
};

void tune1(A a)
{
  a.play();
}

void tune2(A *a)
{
  a->play();
}

int main(int argc , char ** argv)
{
    Eigen::Matrix3d max_33;
    //max_33 = Eigen::Matrix3d::Random();
    
    max_33 << 0,-3,2,3,0,-1,2,-1,0;
    cout << max_33 <<endl;
    cout << max_33.determinant() << endl;

    return 0;
}
