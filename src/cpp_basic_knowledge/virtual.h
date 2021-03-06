//
// Created by wzq on 2020/11/22.
//

#ifndef LEETCODE_VIRTUAL_H
#define LEETCODE_VIRTUAL_H

#include<iostream>
#include<stdio.h>
using namespace std;

class VA
{
public:
    VA() {
        printf("A执行构造函数\n");
    };
    virtual ~VA() {
        printf("A执行析构函数\n");
    };
    void foo()
    {
        printf("A执行非虚函数1\n");
    }
    virtual void fun()
    {
        printf("A执行虚函数2\n");
    }
};
class VB : public VA
{
public:
    VB() {
        printf("B执行构造函数\n");
    };
    ~VB() {
        printf("B执行析构函数\n");
    };
    void foo()
    {
        printf("B执行非虚函数3\n");
    }
    void fun()
    {
        printf("B执行继承父类虚函数4\n");
    }
};
int test_virtual(void)
{
/*    cout <<"创建Ａ的对象"<< endl;
    VA a;
    a.foo();
    a.fun();
    cout<< endl;

    cout <<"创建B的对象"<< endl;
    VB b;
    b.foo();
    b.fun();
    cout<< endl;

    cout <<"创建指向Ａ类的Ａ类指针"<< endl;
    VA *p1 = new VA();
    p1->foo();
    p1->fun();
    cout<< endl;

    cout <<"创建指向B类的B类指针"<< endl;
    VB *p2 = new VB;
    p2->foo();
    p2->fun();
    cout<< endl;*/

    cout <<"创建指向B类的Ａ类指针,系统会自动调用到Ｂ类的虚函数"<< endl;
    VA *p3 = new VB();//A *p3 = &b; 这样定义也可以
    p3->foo();
    p3->fun();
    delete p3;
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

#endif //LEETCODE_VIRTUAL_H
