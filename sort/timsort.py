MINRUN = 4


def count_run(list, lo, hi):
    if lo > hi:
        return (0, True)

    if lo == hi:
        return (1, True)

    i = lo
    if list[i+1] >= list[i]:
        while i < hi and list[i+1] >= list[i]:
            i += 1
        return (i - lo + 1, True)
    else:
        while i < hi and list[i+1] < list[i]:
            i += 1
        return (i - lo + 1, False)


def swap(list, i, j):
    (list[i], list[j]) = (list[j], list[i])


def reverse(list, lo, hi):
    while lo < hi:
        swap(list, lo, hi)
        lo += 1
        hi -= 1


def insertion_sort_part(list, lo, hi, current):
    # print 'insertion sort, lo: {}, hi: {}, current: {}, list[lo:hi+1]: {}'.format(lo, hi, current, list[lo:hi+1])
    for i in xrange(current, hi + 1):
        temp = list[i]
        j = i
        while list[j - 1] > temp and j > lo:
            list[j] = list[j - 1]
            j -= 1
        list[j] = temp

        # print 'i:', i, ', list[lo:hi+1]:', list[lo:hi+1]


def merge(list, run1, run2):

    # print 'merge:', (run1, run2)

    lo1 = run1[0]
    hi1 = run1[0] + run1[1] - 1

    lo2 = run2[0]
    hi2 = run2[0] + run2[1] - 1

    i = lo1
    j = lo2

    out_list = []

    while i <= hi1 and j <= hi2:
        while i <= hi1 and list[i] <= list[j]:
            # print 'i:', i, list[i], list[j]
            out_list.append(list[i])
            i += 1

        while j <= hi2 and list[j] <= list[i]:
            # print 'j:', j, list[j], list[i]
            out_list.append(list[j])
            j += 1

    while i <= hi1:
        # print 'i:', i, list[i]
        out_list.append(list[i])
        i += 1

    while j <= hi2:
        # print 'j:', j, list[j]
        out_list.append(list[j])
        j += 1

    i = 0
    while i <= len(out_list) - 1:
        list[lo1 + i] = out_list[i]
        i += 1


def merge_collapse(list, pendingRuns):

    # print 'merge_collapse, pendingRuns:', pendingRuns

    if len(pendingRuns) <= 1:
        return

    if len(pendingRuns) == 2 and pendingRuns[0][1] <= pendingRuns[1][1]:
        merge(list, pendingRuns[0], pendingRuns[1])
        pendingRuns[0] = (pendingRuns[0][0], pendingRuns[0][1] + pendingRuns[1][1])  # update len
        del pendingRuns[1]

        # print 'list[{}:{}] after merge: {}, pendingRuns: {}'.format(pendingRuns[0][0], pendingRuns[0][1], list[pendingRuns[0][0]:pendingRuns[0][1]], pendingRuns)

        return

    i = len(pendingRuns) - 3    # point to first element of the last triplet

    while i >= 0:
        j = -1
        if pendingRuns[i][1] <= (pendingRuns[i + 1][1] + pendingRuns[i + 2][1]):
            # merge 1 and 2
            # print 'merge 1 and 2'
            j = i
        elif pendingRuns[i + 1][1] <= pendingRuns[i + 2][1]:
            # merge 2 and 3
            j = i+1

        if j >= 0:
            merge(list, pendingRuns[j], pendingRuns[j + 1])
            pendingRuns[j] = (pendingRuns[j][0], pendingRuns[j][1] + pendingRuns[j+1][1])  # update len
            del pendingRuns[j + 1]

            # print 'merge_collapse, pendingRuns after collapse:', pendingRuns

        i -= 1


def merge_collapse_force(list, pendingRuns):

    # print 'merge_collapse_force, pendingRuns:', pendingRuns

    if len(pendingRuns) <= 1:
        return

    i = len(pendingRuns) - 3    # point to first element of the last triplet

    while len(pendingRuns) > 1:
        # merge 2 and 3
        j = i+1

        if (len(pendingRuns) == 2):
            j = 0
        elif pendingRuns[i][1] <= pendingRuns[i + 1][1] + pendingRuns[i + 2][1]:
            # merge 1 and 2
            j = i

        # print 'j: ', j, 'i:', i

        merge(list, pendingRuns[j], pendingRuns[j + 1])
        pendingRuns[j] = (pendingRuns[j][0], pendingRuns[j][1] + pendingRuns[j+1][1])  # update len
        del pendingRuns[j + 1]

        i -= 1


def timsort(list, trace=False):

    # print
    # print 'timsort'

    i = 0

    pendingRuns = []  # (index, len)

    while i < len(list):
        # print 'i: ', i, ', list[i:i+50]: ', list[i:i+50]

        (n, asc) = count_run(list, i, len(list) - 1)

        # print 'run: ', n, ', asc: ', asc

        if not asc:
            reverse(list, i, i + n - 1)
            # print 'list[{}:{}]: {}'.format(i, i + n - 1, list[i:i+n])

        if n < MINRUN:
            hi = min(i + MINRUN - 1, len(list) - 1)
            insertion_sort_part(list, i, hi, i + n)

            n = hi - i + 1

            # print 'after insertion sort, updated n: {}, list: {}'.format(n, list[i:i+n], list)


        pendingRuns.append((i, n))

        merge_collapse(list, pendingRuns)

        i += n

    merge_collapse_force(list, pendingRuns)

    return list
