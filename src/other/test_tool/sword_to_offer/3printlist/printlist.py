#! /usr/bin/python
# -*- coding:utf-8 -*-
class Solution:
    # s 源字符串
    def replaceSpace(self, s):
        # write code here
        s1 = s.replace(" ","%20")
        return s1

if __name__=="__main__":
    sol=Solution()
    string='We Are Happy'
    #s=string.replace(" ","%20")
    s=sol.replaceSpace(string)
    print s
    #sol.replaceSpace(string)

  










   
