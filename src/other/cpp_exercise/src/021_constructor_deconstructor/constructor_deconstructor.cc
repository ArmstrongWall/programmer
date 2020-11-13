/*
 *Time：=======2017.08.22.11:12(星期二)======= 
  Author:JohnnyWang
Function: 分析C++构造析构函数的作用
 *在C++中，普通的对象只有离开它的作用域之后，它的析构函数会被自动调用，从而销毁这个对象，释放它所占的内存，不会发生内存泄露的问题。
 工作再忙也没个头，科研再搞问题还有，实验室是我们共同的根，此刻需要你回来叙叙旧

 * */
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

  /*直接实例化的对象是放在栈上的，所以调用析构函数时会看到时先进后出的
   *使用指针创建的类放在堆上
   *
   * */
  cout << "使用指针指向一个robot类，只对构造有调用" << endl;
  Robot* p_r = new Robot(1,2);
  cout << "使用指针指向一个robot类，只有delete的时候会去调用析构函数" << endl;
  delete p_r;

  cout << "直接实例化一个robot类，对构造有调用,在离开对象的作用域后才会调用析构函数" << endl;
  Robot a(3,4);
  Robot b(5,6);
  Robot c(7,8);
  
  while(1){}

 

}
