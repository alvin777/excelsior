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