#!/usr/bin/python

import time

from simple_sorts import *
from shell_sort import *
from quick_sort import *
from external_merge_sort import *
from radix_sort import *
from merge_sort import *
from heap_sort import *
from intro_sort import *
from timsort import *

from list_generators import *


result = {}

def run_until(sort_func, max_duration = 1.0, generator = random_generator):
    print sort_func

    duration = 0
    list_size = 100
    while duration < max_duration:
        randomList = [x for x in generator(list_size)]
        time_start = time.time()
        try:
            sort_func(randomList)
        except RuntimeError:
            print 'failed on list size: %5d' % list_size
            return

        duration = time.time() - time_start
        print 'list size: %7d, duration: %0.3f' % (list_size, duration)
        if not generator in result:
            result[generator] = {}
        if not list_size in result[generator]:
            result[generator][list_size] = {}
        result[generator][list_size][sort_func] = duration

        list_size *= 2


def test_run_benchmarks():

    generators_list = [random_generator, almost_sorted_generator, reverse_sorted_generator, few_uniq_generator]
    # generators_list = [random_generator, reverse_sorted_generator]
    # generators_list = [few_uniq_generator]
    # sort_func_list = [bubble_sort, insertion_sort, insertion_sort2]
    sort_func_list = [bubble_sort, insertion_sort, insertion_sort2, selection_sort, shell_sort, \
                      merge_sort, quick_sort, lambda x: quick_sort(x, splitByMedian), heap_sort, 
                      lambda x: radix_sort(x, 1000), intro_sort, timsort]
    # sort_func_list = [quick_sort, \
    #                   lambda x: quick_sort(x, partition_func=splitByMiddleElement), \
    #                   lambda x: quick_sort(x, partition_func=splitByMedian), \
    #                   lambda x: quick_sort(x, leaf_sort_func=leaf_insertion_sort)]
    # sort_func_list = [radix_sort, \
    #                   lambda x: radix_sort(x,     2), \
    #                   lambda x: radix_sort(x,   100), 
    #                   lambda x: radix_sort(x,  1000), 
    #                   lambda x: radix_sort(x, 10000)
    #                   ]

    for generator in generators_list:
        print generator
        for sort_func in sort_func_list:
            run_until(sort_func, 0.5, generator)

    for generator in generators_list:
        print generator
        for list_size in sorted(result[generator]):
            sys.stdout.write(str(list_size) + "\t")
            for sort_func in sort_func_list:
                if sort_func in result[generator][list_size]:
                    sys.stdout.write("{:.3f}\t".format(result[generator][list_size][sort_func]))
                else:
                    sys.stdout.write("\t")
            sys.stdout.write("\n")


test_run_benchmarks()