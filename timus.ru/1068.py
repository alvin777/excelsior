import sys

value = int(raw_input())

if value > 0:
    print (value + 1) * value / 2
elif value == 0:
    print 1
else:
    print -(value - 1) * value / 2 + 1