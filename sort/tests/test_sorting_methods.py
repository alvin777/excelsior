#!/usr/bin/env python

import unittest
import filecmp

# add parent folder to import
import os.path
import sys
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), os.pardir))

from simple_sorts import *
from shell_sort import *
from quick_sort import *
from external_merge_sort import *
from radix_sort import *
from merge_sort import *
from heap_sort import *
from intro_sort import *

from list_generators import *


class TestSortingMethods(unittest.TestCase):
    def setUp(self):
        random.seed()


    def test_bubble_sort(self):
        self.assertEqual(bubble_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(bubble_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(1000)]
        self.assertEqual(bubble_sort(randomList), sorted(randomList))


    def test_selection_sort(self):
        self.assertEqual(selection_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(selection_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(1000)]
        self.assertEqual(selection_sort(randomList), sorted(randomList))


    def test_insertion_sort(self):
        self.assertEqual(insertion_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(insertion_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(1000)]
        self.assertEqual(insertion_sort(randomList), sorted(randomList))


    def test_shell_sort(self):
        self.assertEqual(shell_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(shell_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(1000)]
        self.assertEqual(shell_sort(randomList), sorted(randomList))


    def test_insertion_sort2(self):
        self.assertEqual(insertion_sort2([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(insertion_sort2([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(1000)]
        self.assertEqual(insertion_sort2(randomList), sorted(randomList))


    def test_merge_sort(self):
        self.assertEqual(merge_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(merge_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(merge_sort(randomList), sorted(randomList))

    # def test_file_merge_sort(self):
    #     os.remove("small_out.dat")
    #     file_merge_sort("small.dat", "small_out.dat")

    #     prev_word = 0
    #     with open("small_out.dat", "rb") as infile:
    #         while True:
    #             word = infile.read(4)

    #             if word == "":
    #                 return

    #             self.assertTrue(word >= prev_word, "{0} should be > {1}".format(word, prev_word))
    #             prev_word = word

    # def test_large_file_merge_sort(self):
    #     file_merge_sort("large.dat", "large_out.dat")

    #     prev_word = 0
    #     with open("large_out.dat", "rb") as infile:
    #         while True:
    #             word = infile.read(4)

    #             if word == "":
    #                 return

    #             self.assertTrue(word >= prev_word, "{0} should be > {1}".format(word, prev_word))
    #             prev_word = word

    def test_external_merge_sort(self):
        if os.path.exists("small2_out.dat"):
            os.remove("small2_out.dat")
        if os.path.exists("temp.dat"):
            os.remove("temp.dat")
        external_merge_sort("small2.dat", "small2_out.dat", word_size = 1, memory_limit=3)

        self.assertTrue(filecmp.cmp('small2_out.dat', 'small2_sorted.dat'), "{0} should be identical to {1}".format('small2_out.dat', 'small2_sorted.dat'))


    def test_quick_sort(self):
        self.assertEqual(quick_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(quick_sort(randomList), sorted(randomList))


    def check_list(self, list):
        self.assertEqual(splitByMedian(list, 0, 2), 1)
        self.assertEqual(list, [1,2,3])


    def test_split_by_median(self):
        self.check_list([1,2,3])
        self.check_list([1,3,2])
        self.check_list([2,1,3])
        self.check_list([2,3,1])
        self.check_list([3,2,1])
        self.check_list([3,1,2])


    def test_quick_sort_mid(self):
        self.assertEqual(quick_sort([1,2,3,4,5,6,9,8,7], partition_func=splitByMiddleElement), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([9,8,7,6,5,4,3,2,1], partition_func=splitByMiddleElement), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([6,8,4,9,5,3,1,2,7], partition_func=splitByMiddleElement), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(quick_sort(randomList, partition_func=splitByMiddleElement), sorted(randomList))


    def test_quick_sort_median(self):
        self.assertEqual(quick_sort([1,2,3,4,5,6,9,8,7], partition_func=splitByMedian), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([9,8,7,6,5,4,3,2,1], partition_func=splitByMedian), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([6,8,4,9,5,3,1,2,7], partition_func=splitByMedian), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(quick_sort(randomList, partition_func=splitByMedian), sorted(randomList))
        reverseSorted = [x for x in reverse_sorted_generator(20)]
        self.assertEqual(quick_sort(reverseSorted, partition_func=splitByMedian), sorted(reverseSorted))


    def test_quick_sort_leaf_opt(self):
        self.assertEqual(quick_sort([1,2,3,4,5,6,9,8,7], leaf_sort_func=leaf_insertion_sort), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(quick_sort([6,8,4,9,5,3,1,2,7], leaf_sort_func=leaf_insertion_sort), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(quick_sort(randomList, leaf_sort_func=leaf_insertion_sort), sorted(randomList))


    def test_heap_sort(self):
        list = [1,2,3,4,5,6]
        heapify(list, len(list))
        self.assertEqual(sorted(list), [1,2,3,4,5,6])
        for i in xrange(len(list)/2):
            if (i+1)*2-1 < len(list):
                # print "i: {}, list[i]: {}, (i+1)*2-1: {}, list[(i+1)*2-1]: {}".format(i, (i+1)*2-1, list[i], list[(i+1)*2-1]);
                self.assertTrue(list[i] > list[(i+1)*2-1])
            if (i+1)*2 < len(list):
                self.assertTrue(list[i] > list[(i+1)*2])

        self.assertEqual(heap_sort([1,2,3,4,5,6]), [1,2,3,4,5,6])
        self.assertEqual(heap_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(heap_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(heap_sort(randomList), sorted(randomList))


    def test_count_sort(self):
        self.assertEqual(count_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(count_sort([16,8,4,19,5,23,1,2,7]), [1,2,4,5,7,8,16,19,23])
        randomList = [int(random.random()*10000) for _ in xrange(10000)]
        self.assertEqual(count_sort(randomList), sorted(randomList))


    def test_radix_sort(self):
        self.assertEqual(radix_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(radix_sort([16,8,4,19,5,23,1,2,7]), [1,2,4,5,7,8,16,19,23])
        randomList = [int(random.random())*10000000 for _ in xrange(10000)]
        self.assertEqual(radix_sort(randomList), sorted(randomList))
        self.assertEqual(radix_sort(randomList, 2), sorted(randomList))
        self.assertEqual(radix_sort(randomList, 100), sorted(randomList))


    def test_intro_sort(self):
        self.assertEqual(intro_sort([1,2,3,4,5,6,9,8,7]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(intro_sort([9,8,7,6,5,4,3,2,1]), [1,2,3,4,5,6,7,8,9])
        self.assertEqual(intro_sort([6,8,4,9,5,3,1,2,7]), [1,2,3,4,5,6,7,8,9])
        randomList = [random.random() for _ in xrange(10000)]
        self.assertEqual(intro_sort(randomList), sorted(randomList))

        # intro_sort([x for x in almost_sorted_generator(1000)])

        # for (left, right) in sorted(depthHistogram):
        #     print left, right, depthHistogram[(left, right)]

if __name__ == '__main__':
    unittest.main()