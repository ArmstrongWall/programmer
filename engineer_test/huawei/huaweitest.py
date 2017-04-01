#!/usr/bin/python
def choose(a,list):
    i=0;
    while a>=0:
        list[i]=a%10
        a/=10
        i = i+1
        if a==0:
            list.reverse()
            break
    base = 1
    flag = 0
    for j in range(0,5):
        if( list[j]!=0 or flag ==1 ):
            flag = 1
            a=a+list[j]*base
            print list[j]
            base = base*10
    return a
                

def rev_add(a,b):
    if (a>70000 or a<1):
        return 0
    if (b>70000 or b<1):
        return 0
    
    lista = [0,0,0,0,0]
    sum1 = choose(a,lista)

    listb = [0,0,0,0,0]
    sum2 = choose(b,listb)

    num=sum1+sum2
    return num

if __name__ == "__main__":
    a = input("input a: ");
    b = input("input b: ");
    num = rev_add(a,b)
    if (num == 0):
        print "input error"
    else:
        print num

