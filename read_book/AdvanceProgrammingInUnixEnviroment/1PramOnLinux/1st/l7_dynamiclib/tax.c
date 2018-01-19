/*filename:tax.c
 * 创建时间：20160529
 * 创建者：汪自强
 * 程序说明：个人税率计算函数库
 * */
#include<stdio.h>
#include"tax.h"
int tax(int salary,int insurance)
{
    int tax_salary =  salary - insurance;

    int tmp = tax_salary - 3500;

    if(tmp < 0)
    {
        printf("you needn't to tax\n");
        return 0;
    }

    if(tmp <= 1500)
        return (tmp*0.03-0);

    if(tmp >1500&& tmp <=4500)
        return (tmp*0.1-105);

    if(tmp >4500&& tmp <=9000)
        return (tmp*0.2-555);


    if(tmp >9000&& tmp <=35000)
        return (tmp*0.25-1005);

    if(tmp >35000&& tmp <=55000)
        return (tmp*0.3-2755);

    if(tmp >55000&& tmp <=80000)
        return (tmp*0.35-5505);

    if(tmp >80000)
        return (tmp*0.45-13505);
}

