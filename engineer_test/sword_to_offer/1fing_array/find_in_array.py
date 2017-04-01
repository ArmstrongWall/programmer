#!/usr/bin/python
# -*- coding:utf-8 -*-
class Solution:
    # array 二维列表
    def Find(self, target, array):
        # write code here
        list = array
        if(len(list[0])==0):
            return 0
        #list=[[1,2,3,4,5],[5,6,7,8,9],[9,10,11,12,13],[13,14,15,16,17]]
        col  = len(list[0])-1
        row  = len(list)-1
        #print col,row
        if(target>list[row][col] or target<list[0][0]):
            return 0

        for i in range(0,row+1,1):
            j=col
            if(target>list[i][j]):
                for m in range(1,row+1,1):
                    if(target==list[m][j]):
                        return 1
            elif(target<list[i][j]):
                for n in range(0,col,1):
                    if(target==list[i][n]):
                        return 1
            else:
                return 1

        return 0



if __name__ == '__main__':
    #raw=input("输入数组的行数:")
    #list=[0 for i in range(raw)]
    #for i in range(0,raw):
    #    print "输入第",i+1,"行数字，并以逗号隔开"
    #    list[i]=raw_input()
    #target_num=input("输入目标数字")'

    #list=[[1,2,3,4,5],[5,6,7,8,9],[9,10,11,12,13],[13,14,15,16,17]]
    list=[[]]
    S1=Solution()
    #S1.Find(target_num,list)
    OK=S1.Find(7,list)
    print OK


