#include<iostream> 
#include<stdio.h>   
using namespace std;  
  
class A  
{  
public:  
    void foo()  
    {  
        printf("A执行非虚函数1\n");  
    }  
    virtual void fun()  
    {  
        printf("A执行虚函数2\n");  
    }  
};  
class B : public A  
{  
public:  
    void foo()  
    {  
        printf("B执行非虚函数3\n");  
    }  
    void fun()  
    {  
        printf("B执行继承父类虚函数4\n");  
    }  
};  
int main(void)  
{  
    cout <<"创建Ａ的对象"<< endl;
    A a;  
    a.foo();
    a.fun();
    cout<< endl;

    cout <<"创建B的对象"<< endl;
    B b; 
    b.foo();
    b.fun(); 
    cout<< endl;

    cout <<"创建指向Ａ类的Ａ类指针"<< endl;
    A *p1 = new A();  
    p1->foo();  
    p1->fun();  
    cout<< endl;

    cout <<"创建指向B类的B类指针"<< endl;
    B *p2 = new B;  
    p2->foo();  
    p2->fun();  
    cout<< endl;

    cout <<"创建指向B类的Ａ类指针,系统会自动调用到Ｂ类的虚函数"<< endl;
    A *p3 = new B();//A *p3 = &b; 这样定义也可以
    p3->foo();  
    p3->fun();
    cout<< endl;  
 
/*  
　　报错， 无法创建一个指向父类的指针
    cout <<"创建指向Ａ类的Ｂ类指针,系统会自动调用到Ｂ类的虚函数"<< endl;
    B *p4 = new A(); 
    p4->foo();  
    p4->fun();
    cout<< endl;  
*/

    return 0;  




}  
