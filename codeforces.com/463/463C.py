# import unittest
import sys
import gc; gc.disable()

def read_data():
    data = []

    # for i in xrange(size):
    #     data.append([int(x) for x in raw_input().strip().split()])
    for line in sys.stdin:
        data.append([int(x) for x in line.split()])

    return data

    

def calc_max_value(data):

    len_data = len(data)

    # calc diag
    tr_dial_sum = [0] * (len_data * 2 + 1)
    br_diag_sum = [0] * (len_data * 2 + 1)

    for i in xrange(len_data):
        for j in xrange(len_data):
            tr_dial_sum[i + j] += data[i][j]
            br_diag_sum[len_data/2 + 1 + i - j] += data[i][j]

    # i = 0
    # for row in data:
    #     j = 0
    #     for cell in row:
    #         j += 1
    #         tr_dial_sum[i + j] += cell
    #         br_diag_sum[len_data/2 + 1 + i - j] += cell

    #     i += 1


    # print "diag calculated"


    max_sum_value_list = [-1, -1]
    cells_list = [(-1, -1), (-1, -1)]
    for i in xrange(len_data):
        sum_row = []
        for j in xrange(len_data):
            sum_value = tr_dial_sum[i + j] + br_diag_sum[len_data/2 + 1 + i - j] - data[i][j]

            if sum_value > max_sum_value_list[(i + j) % 2]:
                max_sum_value_list[(i + j) % 2] = sum_value
                cells_list[(i + j) % 2] = (i + 1, j + 1)

    return max_sum_value_list, cells_list


# class TestCalcMaxValue(unittest.TestCase):
#     def test_simple(self):

#         data = ((1, 1, 1, 1),
#                 (2, 1, 1, 0),
#                 (1, 1, 1, 0),
#                 (1, 0, 0, 1))
        
#         print data
#         max_sum_value_list, cells_list = calc_max_value(data)

#         print sum(max_sum_value_list)
#         print " ".join(map(str, cells_list[0] + cells_list[1]))


size = input()
data = read_data()

# print "data read"

max_sum_value_list, cells_list = calc_max_value(data)

print max_sum_value_list
print sum(max_sum_value_list)
print " ".join(map(str, cells_list[0] + cells_list[1]))


# if __name__ == '__main__':
#     unittest.main()