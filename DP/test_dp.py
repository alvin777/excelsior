#!/bin/python

data = ((1, 2, 3),
        (5, 6, 7), 
        (7, 8, 9))

result = [[0 for _ in xrange(len(data))] for _ in xrange(len(data))]
direction = [[0 for _ in xrange(len(data))] for _ in xrange(len(data))]

def print_matrix(matrix):
    for row in matrix:
        print map(str, [x for x in row])

def run_dp(data):
    path = ""
    for i in xrange(len(data)):
        for j in xrange(len(data[i])):
            if i == 0 and j == 0:
                result[i][j] = data[i][j]
                direction[i][j] = ""
                step = ""
                continue

            # if i > 0 and j > 0:
            #     if result[i - 1][j] > result[i][j - 1]:
            #         result[i][j] = result[i - 1][j] + data[i][j]
            #         direction[i][j] = direction[i - 1][j] + "D"
            #     else:
            #         result[i][j] = result[i][j - 1] + data[i][j]
            #         direction[i][j] = direction[i][j - 1] + "R"
            # elif i > 0:
            #     result[i][j] = result[i - 1][j] + data[i][j]
            #     direction[i][j] = direction[i - 1][j] + "D"
            # else:
            #     result[i][j] = result[i][j - 1] + data[i][j]
            #     direction[i][j] = direction[i][j - 1] + "R"

            if i > 0 and j > 0 and result[i - 1][j] > result[i][j - 1] or j == 0:
                result[i][j] = result[i - 1][j] + data[i][j]
                # direction[i][j] = direction[i - 1][j] + "D"
                direction[i - 1][j] = "D"
            else:
                result[i][j] = result[i][j - 1] + data[i][j]
                # direction[i][j] = direction[i][j - 1] + "R"
                direction[i][j - 1] = "R"


run_dp(data)
# print "\n".join(str(x) for x in [line for line in result])

print "data:"
print_matrix(data)

print "result:"
print_matrix(result)

print "direction"
print_matrix(direction)
