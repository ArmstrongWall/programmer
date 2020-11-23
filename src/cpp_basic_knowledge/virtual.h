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
    void foo()
    {
        printf("Aִ�з��麯��1\n");
    }
    virtual void fun()
    {
        printf("Aִ���麯��2\n");
    }
};
class VB : public VA
{
public:
    void foo()
    {
        printf("Bִ�з��麯��3\n");
    }
    void fun()
    {
        printf("Bִ�м̳и����麯��4\n");
    }
};
int test_virtual(void)
{
    cout <<"�������Ķ���"<< endl;
    VA a;
    a.foo();
    a.fun();
    cout<< endl;

    cout <<"����B�Ķ���"<< endl;
    VB b;
    b.foo();
    b.fun();
    cout<< endl;

    cout <<"����ָ�����ģ���ָ��"<< endl;
    VA *p1 = new VA();
    p1->foo();
    p1->fun();
    cout<< endl;

    cout <<"����ָ��B���B��ָ��"<< endl;
    VB *p2 = new VB;
    p2->foo();
    p2->fun();
    cout<< endl;

    cout <<"����ָ��B��ģ���ָ��,ϵͳ���Զ����õ�������麯��"<< endl;
    VA *p3 = new VB();//A *p3 = &b; ��������Ҳ����
    p3->foo();
    p3->fun();
    cout<< endl;

/*
�������� �޷�����һ��ָ�����ָ��
    cout <<"����ָ�����ģ���ָ��,ϵͳ���Զ����õ�������麯��"<< endl;
    B *p4 = new A();
    p4->foo();
    p4->fun();
    cout<< endl;
*/

    return 0;
}

#endif //LEETCODE_VIRTUAL_H
