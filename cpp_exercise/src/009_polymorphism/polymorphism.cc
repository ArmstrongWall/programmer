#include<iostream>
#include<vector>

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
  A a;
  tune1(a);
  
  B b1;
  tune1(b1);//不是指针就无法实现多态

  B b2;
  tune2(&b2);

  return 0;
}
