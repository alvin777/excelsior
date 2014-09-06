#!/usr/bin/env python

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
        print "after swap:", list[left:right+1]

    # i = left
    # j = right
    # while i < j:
    #     # print "i: ", i, ", j: ", j
    #     while list[i] < pivot_value and i < j:
    #         i += 1

    #     while list[j] >= pivot_value and i < j:
    #         j -= 1

    #     # print "swapping [", i, "] ", list[i], " and [", j, "]", list[j]
    #     swap(list, i, j)

    # dutch flag
    lt = left
    gt = right - 1
    i = left
    while i <= gt:
        if trace:
            print list[left:right+1], "i:", i, " lt:", lt, " gt:", gt

        if list[i] < pivot_value:
            swap(list, i, lt)
            lt += 1
            i += 1
        elif list[i] > pivot_value:
            swap(list, i, gt)
            gt -= 1
        else:
            i += 1 

    # return pivot
    swap(list, i, right)

    if trace:
        # print " " * 3, "range after: ", list[left:right+1]
        print list[left:right+1], "i:", i, " lt:", lt, " gt:", gt
    # we need to go deeper
    # quick_sort_part(list, left, i - 1, partition_func, leaf_sort_func, trace)
    # quick_sort_part(list, i + 1, right, partition_func, leaf_sort_func, trace)
    quick_sort_part(list, left, lt - 1, partition_func, leaf_sort_func, trace)
    quick_sort_part(list, gt+2, right, partition_func, leaf_sort_func, trace)


def quick_sort(list, partition_func = splitByLastElement, leaf_sort_func = None, trace = False):
    # print
    quick_sort_part(list, 0, len(list) - 1, partition_func, leaf_sort_func, trace)
    return list
