def generate_shell_sort_gaps(length):
    gapsList = [1]
    k = 1

    while length > gapsList[-1]:
        gapsList.append(pow(4, k) + 3*pow(2, k-1) + 1)
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
