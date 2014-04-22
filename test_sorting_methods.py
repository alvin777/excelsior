import unittest
import random
import time
import os
import math
import sys

def bubble_sort(list):
    while True:
        changed = False
        for i in xrange(len(list) - 1):
            if (list[i] > list[i+1]):
                temp = list[i]
                list[i] = list[i+1]
                list[i+1] = temp
                changed = True

        if not changed:
            break

    return list

def selection_sort(list):
    for i in xrange(len(list) - 1):
        min = list[i]
        min_index = i
        min_found = False

        for j in xrange(i + 1, len(list)):
            if (list[j] < min):
                min = list[j]
                min_index = j
                min_found = True

        if (min_found):
            temp = list[i]
            list[i] = list[min_index]
            list[min_index] = temp

    return list

#  0  1  2  3  4  5
# [1, 2, 9, 6, 2, 4]
#  ~~~~~~|~ |
#       ins i

def insertion_sort(list):
    for i in xrange(1, len(list)):
        insert_index = i
        for j in xrange(i - 1, -1, -1):
            if list[i] < list[j]:
                insert_index = j
            else:
                break
        
        if insert_index != i:
            temp = list[i]
            # slide
            for k in xrange(i, insert_index, -1):
                list[k] = list[k - 1]
            list[insert_index] = temp


    return list

#  0  1  2  3  4  5
# [1, 2, 9, 6, 2, 4]
#  ~~~~~~|~ |
#        j  i

def insertion_sort2(list):
    for i in xrange(1, len(list)):
        temp = list[i]
        j = i
        while list[j - 1] > temp and j > 0:
            list[j] = list[j - 1]
            j = j - 1
        list[j] = temp
    return list

def generate_shell_sort_gaps(length):
    gapsList = [1]
    k = 1
    
    while length > gapsList[-1]:
        gapsList.append(pow(4,k) + 3*pow(2, k-1) + 1)
        k += 1

    return gapsList[:-1][::-1]

def shell_sort(list):

    gapsList = generate_shell_sort_gaps(len(list))

    # print gapsList
    
    for gap in gapsList:
        # print "gap:", gap

        for i in xrange(gap, len(list)):
            value = list[i]
            j = i
            while j-gap >= 0 and list[j-gap] > value:
                list[j] = list[j-gap]
                j -= gap
            list[j] = value

        # print "list:", list

    return list

#  chunk_size = 4
#  0  1  2  3  4  5  6
# [1, 3, 7, 2, 4, 5, 6]
#  i           j

def merge_list_chunks(list, i, j, chunk_size, list_size):
    original_i = i
    max_i = min(i + chunk_size, list_size)
    max_j = min(j + chunk_size, list_size)
    out = [0] * (chunk_size*2)
    k = 0

    # print
    # print "before merge: ", list, ", i: ", i, ", j: ", j, ", chunk_size: ", chunk_size, ", list_size: ", list_size, ", max_i: ", max_i, ", max_j: ", max_j
    # print

    while i < max_i or j < max_j:
        while (i < max_i and (j >= max_j or list[i] <= list[j])):
            out[k] = list[i]
            k += 1
            i += 1
            # print "i: ", i, ", j: ", j, ", k: ", k

        while (j < max_j and (i >= max_i or list[j] <= list[i])):
            out[k] = list[j]
            k += 1
            j += 1

    # print "out: ", out[:k]

    for l in xrange(k):
        list[original_i + l] = out[l]

    # print "after merge: ", list


def merge_sort(list):
    chunk_size = 1

    while chunk_size < len(list):
        # print "chunk_size: ", chunk_size
        i = 0
        j = chunk_size
        while i < len(list):
            merge_list_chunks(list, i, j, chunk_size, len(list))

            i += chunk_size*2
            j += chunk_size*2

        chunk_size *= 2
    return list


ELEMENT_SIZE = 4

def file_merge_chunks(infile1, infile2, outfile, i, j, chunk_size, infile_size):

    max_i = min(i + chunk_size, infile_size)
    max_j = min(j + chunk_size, infile_size)

    # print "i: ", i, ", j: ", j

    infile1.seek(i, 0)
    element_i = infile1.read(ELEMENT_SIZE)
    infile2.seek(j, 0)
    element_j = infile2.read(ELEMENT_SIZE)

    while i < max_i or j < max_j:

        while (i < max_i and (element_i <= element_j or j >= max_j)):
            outfile.write(element_i)
            element_i = infile1.read(ELEMENT_SIZE)
            i += ELEMENT_SIZE

        while (j < max_j and (element_j <= element_i or i >= max_i)):
            outfile.write(element_j)
            element_j = infile2.read(ELEMENT_SIZE)
            j += ELEMENT_SIZE


def file_merge_sort(infilename, outfilename):
    chunk_size = 4
    TEMP_FILE_NAME = "temp.dat"

    with open(infilename, "r") as infile:
        infile.seek(0, 2)
        infile_size = infile.tell()
        infile.seek(0, 0)

    current_infilename = infilename
    current_outfilename = outfilename

    while chunk_size < infile_size:
        i = 0
        j = chunk_size

        # print "current_infilename: ", current_infilename, ", current_outfilename: ", current_outfilename

        with open(current_infilename, "r") as infile1, \
             open(current_infilename, "r") as infile2, \
             open(current_outfilename, "w") as outfile:

            while i < infile_size:
                file_merge_chunks(infile1, infile2, outfile, i, j, chunk_size, infile_size)

                i += chunk_size*2
                j += chunk_size*2

        # if chunk_size >= 16: break

        chunk_size *= 2

        # print "current_infilename: ", current_infilename, ", infilename: ", infilename
        if current_infilename == infilename:
            # print "*"
            current_infilename, current_outfilename = current_outfilename, TEMP_FILE_NAME
        else:
            current_infilename, current_outfilename = current_outfilename, current_infilename

    if current_outfilename == TEMP_FILE_NAME:
        os.remove(TEMP_FILE_NAME)
    else:
        os.remove(outfilename)
        os.rename(TEMP_FILE_NAME, outfilename)


def swap(list, i, j):
    list[i], list[j] = list[j], list[i]

def splitByLastElement(list, left, right, trace = False):
    return right

def splitByMiddleElement(list, left, right, trace = False):
    return left + (right - left)/2

def splitByMedian(list, left, right, trace = False):

    if trace:
        print "from: ", left, " to: ", right, list

    med = left + (right - left)/2

    if list[right] < list[med]:
        swap(list, right, med)

    if list[med] < list[left]:
        swap(list, med, left)

    if list[right] < list[med]:
        swap(list, right, med)

    return med

def leaf_insertion_sort(list, left, right):
    if right - left > 10: 
        return False

    for i in xrange(left, right + 1):
        temp = list[i]
        j = i
        while list[j - 1] > temp and j > 0:
            list[j] = list[j - 1]
            j = j - 1
        list[j] = temp

    return True

def quick_sort_part(list, left, right, partition_func = splitByLastElement, leaf_sort_func = None, trace = False):
    if trace:
        print "quick_sort_part from: [", left, "], to: [", right, "], range: ", list[left:right + 1]
        print list

    if left > right: return

    if right - left < 2:
        if list[left] > list[right]:
            swap (list, left, right)
        return

    if not leaf_sort_func is None:
        if leaf_sort_func(list, left, right) == True:
            # print list[left:right]
            return

    # find pivot value
    pivot_index = partition_func(list, left, right, trace)
    pivot_value = list[pivot_index]

    if trace:
        print "pivot_value: ", pivot_value

    # save pivot
    swap(list, pivot_index, right)

    if trace:
        print "after swap:", list

    i = left
    j = right
    while i < j:
        # print "i: ", i, ", j: ", j
        while list[i] < pivot_value and i < j:
            i += 1

        while list[j] >= pivot_value and i < j:
            j -= 1

        # print "swapping [", i, "] ", list[i], " and [", j, "]", list[j]
        swap(list, i, j)

    # return pivot
    swap(list, i, right)

    # print " " * 33, "range after: ", list[left:right+1]

    # we need to go deeper
    quick_sort_part(list, left, i - 1, partition_func, leaf_sort_func, trace)
    quick_sort_part(list, i + 1, right, partition_func, leaf_sort_func, trace)


def quick_sort(list, partition_func = splitByLastElement, leaf_sort_func = None, trace = False):
    # print
    quick_sort_part(list, 0, len(list) - 1, partition_func, leaf_sort_func, trace)
    return list


### heap sort ###

def parent(current):
    return (current-1)/2

def left(current):
    return (current+1)*2-1

def right(current):
    return (current+1)*2

def sift_down(list, subtree_root, length):
    current = subtree_root
    while True:
        # print "current: {}, list[current]: {}".format(current, list[current])
        # print "left:  {}, list[left]:  {}".format(left(current),  list[left(current)]  if left(current) < len(list) else "")  
        # print "right: {}, list[right]: {}".format(right(current), list[right(current)] if right(current) < len(list) else "") 

        maxIndex = current
        if left(current)  < length and list[left(current)]  > list[maxIndex]:
            maxIndex = left(current)

        if right(current) < length and list[right(current)] > list[maxIndex]:
            maxIndex = right(current)

        if maxIndex != current:
            # print "swap {} and {}".format(list[maxIndex], list[current])
            swap(list, current, maxIndex)
        else:
            break;

        current = maxIndex

def heapify(list, length):
    # print list
    current = parent(length)

    while current >= 0:    
        sift_down(list, current, length)
        current -= 1

        # print list


def heap_sort(list):
    heapify(list, len(list))

    sortedIndex = len(list) - 1

    while sortedIndex >= 0:        
        swap(list, 0, sortedIndex)
        # print list[:sortedIndex], list[sortedIndex:]

        sift_down(list, 0, sortedIndex)
        # print ">>", list[:sortedIndex], list[sortedIndex:]

        sortedIndex -= 1

    return list


### radix sort

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

class TestSortingMethods(unittest.TestCase):
    def setUp(self):
        random.seed()

    def run_until(self, sort_func, max_duration = 1.0, generator = random_generator):
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
            if not generator in self.result:
                self.result[generator] = {}
            if not list_size in self.result[generator]:
                self.result[generator][list_size] = {}
            self.result[generator][list_size][sort_func] = duration

            list_size *= 2

    def test_run_benchmarks(self):

        # return

        self.result = {}

        # generators_list = [random_generator, almost_sorted_generator, reverse_sorted_generator, few_uniq_generator]
        # generators_list = [random_generator, reverse_sorted_generator]
        generators_list = [few_uniq_generator]
        # sort_func_list = [bubble_sort, insertion_sort, insertion_sort2]
        sort_func_list = [bubble_sort, insertion_sort, insertion_sort2, selection_sort, shell_sort, \
                          merge_sort, quick_sort, lambda x: quick_sort(x, splitByMedian), heap_sort, 
                          lambda x: radix_sort(x, 1000)]
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
                self.run_until(sort_func, 0.5, generator)

        for generator in generators_list:
            print generator
            for list_size in sorted(self.result[generator]):
                sys.stdout.write(str(list_size) + "\t")
                for sort_func in sort_func_list:
                    if sort_func in self.result[generator][list_size]:
                        sys.stdout.write("{:.3f}\t".format(self.result[generator][list_size][sort_func]))
                    else:
                        sys.stdout.write("\t")
                sys.stdout.write("\n")

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

    def test_file_merge_sort(self):
        file_merge_sort("small.dat", "small_out.dat")

        prev_word = 0
        with open("small_out.dat", "rb") as infile:
            while True:
                word = infile.read(4)

                if word == "":
                    return

                self.assertTrue(word >= prev_word, "{0} should be > {1}".format(word, prev_word))
                prev_word = word

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

if __name__ == '__main__':
    unittest.main()