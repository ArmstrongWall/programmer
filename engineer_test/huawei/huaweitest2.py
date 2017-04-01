!/usr/bin/python
def right(list):
    temp=list[2]
    list[2]=list[0]
    list[0]=list[3]
    list[3]=list[1]
    list[1]=temp

def left(list):
    temp1=list[2]
    list[2]=list[3]
    list[3]=temp1
    temp2=list[0]
    list[0]=list[1]
    list[1]=temp2
    right(list)

def a(list):
    temp=list[4]
    list[4]=list[1]
    list[1]=list[5]
    list[5]=list[0]
    list[0]=temp




list = [1,2,3,4,5,6]

right(list)
a(list)
print list
