#!/usr/bin/env python


def swap(list, i, j):
    list[i], list[j] = list[j], list[i]


def parent(first, current):
    return first + (current - first - 1)/2


def left(first, current):
    return first + (current - first + 1)*2-1


def right(first, current):
    return first + (current - first + 1)*2


def sift_down_part(list, first, current, last):
    while True:
        # print "current: {}, list[current]: {}".format(current, list[current])
        # print "left:  {}, list[left]:  {}".format(left(first, current),  list[left(first, current)]  if left(first, current) < len(list) else "")
        # print "right: {}, list[right]: {}".format(right(first, current), list[right(first, current)] if right(first, current) < len(list) else "")

        maxIndex = current
        if left(first, current) <= last and list[left(first, current)] > list[maxIndex]:
            maxIndex = left(first, current)

        if right(first, current) <= last and list[right(first, current)] > list[maxIndex]:
            maxIndex = right(first, current)

        if maxIndex != current:
            # print "swap {} and {}".format(list[maxIndex], list[current])
            swap(list, current, maxIndex)
        else:
            break

        current = maxIndex


def sift_down(list, current, last):
    sift_down_part(list, 0, current, last);


def heapify_part(list, first, last):
    # print "heapify_part, list:", list
    current = parent(first, last)

    # print "current: ", current

    while current >= first:
        sift_down_part(list, first, current, last)
        current -= 1

        # print list


def heapify(list, length):
    heapify_part(list, 0, length - 1)


def heap_sort_part(list, first, last):
    heapify_part(list, first, last)

    while last > first:
        swap(list, first, last)
        # print list[:last], list[last:]

        sift_down_part(list, first, first, last - 1)
        # print ">>", list[:last], list[last:]

        last -= 1

    return list


def heap_sort(list):
    return heap_sort_part(list, 0, len(list) - 1)
