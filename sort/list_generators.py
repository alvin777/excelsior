import sys
import random
import math

### generators

def random_generator(size):
    counter = 0
    while counter < size:
        counter += 1
        yield int(random.random()*sys.maxint)

def almost_sorted_generator(size, percent=10.0):
    counter = 0
    while counter < size:
        counter += 1
        if counter % (size/(percent/100*size)) == 0:
            yield counter + 1
        elif counter % (size/(percent/100*size)) == 1:
            yield counter - 1
        else:
            yield counter


def reverse_sorted_generator(size):
    counter = 0
    while counter < size:
        counter += 1
        yield size - counter


def few_uniq_generator(size):
    counter = 0
    randomNumbers = [x for x in xrange(int(math.log(size))+1)];
    while counter < size:
        counter += 1
        yield random.choice(randomNumbers)
