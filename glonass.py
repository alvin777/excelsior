#!/usr/bin/python

import hashlib
import array


def generate_hash_array():
    hasharray = array.array('B', [0]*1000000)

    # for i in xrange(0,999999):
    for i in xrange(0, 999999):
        # print i
        string = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446" + str(i)
        # print string

        hash = hashlib.md5(string).hexdigest()
        # print hash[0], hash

        if hash[0] > "7":
            hasharray[i] = 1
        else:
            hasharray[i] = 0

    with open('hasharray.dat', "w") as hashfile:
        hasharray.tofile(hashfile)


def check_array():
    hasharray = array.array('B')

    with open('hasharray.dat', "r") as hashfile:
        hasharray.fromfile(hashfile, 1000000)

    numbersMap = {}
    count = 999999
    # count = 50

    for i in xrange(0, count):
        number = 0
        for j in xrange(0, 40):
            number += (hasharray[(i + j) % count] << j)

        # print "i: {:2}, number: {:020b}".format(i, number)

        if not number in numbersMap:
            numbersMap[number] = [i]
        else:
            numbersMap[number].append(i)

    # print numbersMap

    for k in numbersMap:
        if len(numbersMap[k]) > 1:
            print k, numbersMap[k]

# generate_hash_array()

check_array()
