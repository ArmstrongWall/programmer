#coding=utf-8  
  
import os
path = '/home/wzq/images'
count = 1570
file  = os.listdir(path)
file.sort()
for i in file:
    print(i)
    os.rename(os.path.join(path,i),os.path.join(path,str(count).zfill(5)+".png"))
    count+=1
