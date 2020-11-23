//
// Created by wzq on 2020/11/22.
//

#ifndef LEETCODE_MULTICHILD_H
#define LEETCODE_MULTICHILD_H

#include "iostream"

using namespace std;
class CBase
{
private:
    int a;
public:
    CBase(int va):a(va)
    {
        cout<<"CBase:"<<endl<<this->a<<endl;
    }
};

class A:public CBase
{
private:
    int t;
public:
    A(int vt,int ut):t(vt),CBase(ut)
    {
        cout<<"A:"<<endl<<this->t<<endl;
    }

};

class B:public CBase
{
private:
    int t;
public:
    B(int vt,int ut):t(vt),CBase(ut)
    {
        cout<<"B:"<<endl<<this->t<<endl;
    }
};

class C:public B,public A
{
private:
    int t;
public:
    //C(int vt,int ut,int kt):A(vt,ut),B(vt,ut),CBase(kt)
    C(int vt,int ut,int kt):A(vt,ut),B(vt,ut),t(kt)
    {
        cout<<"C:"<<endl<<this->t<<endl;
    }
};

int test_multichild(void) {
    C cc(1,2,3);
    return 0;
}

#endif //LEETCODE_MULTICHILD_H
