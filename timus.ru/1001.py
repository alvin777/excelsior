import sys
import math

for value in [math.sqrt(float(x)) for x in reversed(sys.stdin.read().split())]:
    print "{:0.4f}".format(value)
