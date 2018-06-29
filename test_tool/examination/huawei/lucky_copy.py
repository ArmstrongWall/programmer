#!/usr/bin/python3
def num_is_lucky( str ):
    res = 0
    for i in str:
        res = int(i) + res
    print res
    a1='{0:b}'.format(int(str))
    print a1
    res1 = 0
    for j in a1:
        res1 = int(j) + res1
    print res1
    if res == res1:
        return 1
    else:
        return 0;

num = raw_input("input N: ");
print "your input num is: ", num
for i in range(1,int(num)):
    ans = num_is_lucky(str(i))
    if ans == 1:
        print "This num is lucky num"
    else:
        print "This num is not lucky num"








