import sys
from pympler.asizeof import asizeof
from array import array

# tuple2 = (1,2)
# tuple10 = (1,2,3,4,5,6,7,8,9,0)

# print asizeof(tuple2), asizeof(tuple10)

# a = array('h', [10 for _ in xrange(1000)])
# a = array('h',[1,2])

a = array('L', [array('h', [1,2,3]) for _ in xrange(10)])

print asizeof(a)
print a.buffer_info()