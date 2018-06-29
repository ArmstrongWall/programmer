#!/usr/bin/python3
def num_is_lucky( num ):
    res = 0
    for i in num:
        res = i + res
    print res
    a1='{0:b}'.format(num)
    print a1
    res1 = 0
    for j in a1:
        res1 = j + res1
    print res1
    if res == res1:
        return 1
    else:
        return 0;

num = raw_input("input N: ");
print "your input num is: ", num
ans = num_is_lucky(8)
if ans == 1:
    print "This num is lucky num"
else:
    print "This num is not lucky num"








