#include<iostream>
using namespace std;

class Robot
{
 private:
  int wheel_num;
  int sensor_num;

 public:
  Robot(int w_m,int s_m):wheel_num(w_m),sensor_num(s_m)
  {
    cout << "A constructor" << endl;
    cout << "robot wheel"   << wheel_num  << endl;
    cout << "robot sensor"  << sensor_num << endl;
  }
  ~Robot()
  {
    cout << "A deconstructor" << endl;
    cout << "robot wheel"   << wheel_num  << endl;
    cout << "robot sensor"  << sensor_num << endl;
  }

};

int main(int  agrc , char * argv[])
{
  cout << "直接实例化一个robot类，对构造和析构函数都有调用" << endl;
  Robot a(1,2);


  cout << "指针指向一个robot类，对构造和析构函数都有调用" << endl;
  Robot *p_r = new Robot(3,4); 
  delete p_r;

}
