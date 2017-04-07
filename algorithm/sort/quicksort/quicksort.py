#!/usr/bin/python
# -*- coding:utf-8 -*-
#import sys   
#sys.setrecursionlimit(1000000) #如果递归深度不够，这里要加，例如这里设置为一百万
class Solution:
    # array 二维列表
    def quicksort(self,list,left,right):
        # write code here
        begin = left
        end   = right
        if end <= begin:
            return
        threshold = list[begin]
        while end > begin :
            while end >begin and list[end] >= threshold :
                end -= 1
            list[begin] = list[end]
            while end >begin and list[begin] <= threshold :
                begin += 1
            list[end] = list[begin]

        list[end] = threshold

        self.quicksort(list,left,begin-1)
        #注意这里第二个参数不能是0
        self.quicksort(list,end+1,right)
        #注意这里的第三个参数不能是数组长度，那样就会陷入死循环
            

if __name__ == '__main__':
    print "Here we go"
    list=[1,2,432,53,56,54,563,14,45]
    S1=Solution()
    end=len(list)-1
    S1.quicksort(list,0,end)
    print list


