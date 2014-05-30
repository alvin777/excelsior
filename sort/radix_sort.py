#!/usr/bin/env python

def count_sort(list):
    max_value = max(list)

    bucket = [0 for _ in xrange(max_value+1)]

    for value in list:
        bucket[value] += 1

    # print "bucket:", bucket

    for i in xrange(1, len(bucket)):
        # if i == 0: continue
        bucket[i] += bucket[i-1]

    # print "cumulative bucket:", bucket

    new_list = [0 for _ in xrange(len(list))]

    for i in xrange(len(list)):
        # print i, list[i], "->new_list", bucket[list[i]]
        bucket[list[i]] -= 1
        new_list[bucket[list[i]]] = list[i]

    return new_list


def radix_sort(list, base=10):

    exp = 1

    max_value = max(list)

    if max_value < 1: return list

    bucket = [0 for _ in xrange(base)]

    while exp < max_value:

        for i in xrange(base):
            bucket[i] = 0

        # split to bucket
        for value in list:
            digit = value//exp % base
            # print value, digit
            bucket[digit] += 1

        # print "bucket:", bucket

        # cumulative sum
        for i in xrange(1, len(bucket)):
            bucket[i] += bucket[i-1]

        # print "cumulative bucket:", bucket

        # reposition
        new_list = [0 for _ in xrange(len(list))]

        for i in xrange(len(list) - 1, -1, -1):
            digit = list[i]//exp % base
            bucket[digit] -= 1
            new_list[bucket[digit]] = list[i]

            # print "list[i]:", list[i], "digit: ", digit, "bucket[digit]: ", bucket[digit]

        # print "list after iteration:", new_list

        list = new_list

        exp *= base

    return list