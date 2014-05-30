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
