import sys
from array import array

N = 1000
# weightMatrix = [[-1 for _ in xrange(N)] for _ in xrange(N)]
weightMatrix2   = [array('i', [-1 for _ in xrange(N)]) for _ in xrange(N)]
weightMatrix5   = [array('i', [-1 for _ in xrange(N)]) for _ in xrange(N)]
weightMatrixDir = [array('c', [' ' for _ in xrange(N)]) for _ in xrange(N)]

indent = -1

def log(*args):
    # return
    sys.stdout.write(" "*indent*4)
    for arg in args:
        sys.stdout.write(str(arg))
    sys.stdout.write('\n')

def numberWeight(number):
    global indent

    originalNumber = number

    twos = 0
    while number % 2 == 0:
        number /= 2
        twos += 1

    fives = 0
    while number % 5 == 0:
        number /= 5
        fives += 1

    # log("numberWeight for ", originalNumber, ": ", (twos, fives))

    return array('h',[twos, fives])

def sumWeight(weight1, weight2):
    # log(weight1, "+", weight2, "=", array('h',[weight1[0] + weight2[0], weight1[1] + weight2[1]]))
    return array('h',[weight1[0] + weight2[0], weight1[1] + weight2[1]])

# def less(weight1, weight2):
#     min1 = min(weight1)
#     min2 = min(weight2)

#     if min1 == min2:
#         return sum(weight1) < sum(weight2)

#     return min1 < min2

def less2(weight1, weight2):
    return weight1[0] < weight2[0]

def less5(weight1, weight2):
    return weight1[1] < weight2[1]

# def weightAndPath(matrix, x, y, less):

#     global indent

#     indent += 1

#     log("weight for: {}, {}".format(x, y))

#     if weightMatrix[y][x] > 0:
#         log("<< cached:", weightMatrix[y][x])
#         indent -= 1
#         return weightMatrix[y][x]

#     if (x,y) == (0,0):
#         weightMatrix[y][x] = numberWeight(matrix[y][x]), ""
#         indent -= 1
#         return weightMatrix[y][x]

#     if x > 0:
#         leftCellWeight, leftCellPath = weightAndPath(matrix, x-1, y, less)

#     if y > 0:
#         topCellWeight, topCellPath = weightAndPath(matrix, x, y-1, less)

#     currentWeight = numberWeight(matrix[y][x])

#     if x == 0:
#         weight = sumWeight(currentWeight, topCellWeight)
#         path = topCellPath + "D"
#     elif y == 0:
#         weight = sumWeight(currentWeight, leftCellWeight)
#         path = leftCellPath + "R"
#     else:
#         log("comparing {} and {}".format(sumWeight(currentWeight, topCellWeight), sumWeight(currentWeight, leftCellWeight)))
#         if less(sumWeight(currentWeight, topCellWeight), sumWeight(currentWeight, leftCellWeight)):
#             weight = sumWeight(currentWeight, topCellWeight)
#             path = topCellPath + "D"
#         else:
#             weight = sumWeight(currentWeight, leftCellWeight)
#             path = leftCellPath + "R"


#     weightMatrix[y][x] = weight, path

#     log("<< return:", weightMatrix[y][x])

#     indent -= 1

#     return weightMatrix[y][x]


def weightAndPathBottomUp(matrix, less):

    for y in xrange(len(matrix)):
        for x in xrange(len(matrix[0])):

            # log("cell: ({}, {})".format(x, y))

            if (x,y) == (0,0):
                currentWeight = numberWeight(matrix[0][0])
                weightMatrix2[0][0] = currentWeight[0]
                weightMatrix5[0][0] = currentWeight[1]
                weightMatrixDir[0][0] = ' '
                continue

            if x > 0:
                leftCellWeight = weightMatrix2[y][x-1], weightMatrix5[y][x-1]

            if y > 0:
                topCellWeight  = weightMatrix2[y-1][x],weightMatrix5[y-1][x]

            currentWeight = numberWeight(matrix[y][x])

            if x == 0:
                weight = sumWeight(currentWeight, topCellWeight)
                path = 'D'
            elif y == 0:
                weight = sumWeight(currentWeight, leftCellWeight)
                path = 'R'
            else:
                topSumWeight = sumWeight(currentWeight, topCellWeight)
                leftSumWeight = sumWeight(currentWeight, leftCellWeight)
                # log("comparing {} and {}".format(str(sumWeight(currentWeight, topCellWeight)), str(sumWeight(currentWeight, leftCellWeight))))
                if less(topSumWeight, leftSumWeight):
                    weight = topSumWeight
                    path = 'D'
                else:
                    weight = leftSumWeight
                    path = 'R'

            weightMatrix2[y][x] = weight[0]
            weightMatrix5[y][x] = weight[1]
            weightMatrixDir[y][x] = path


    x = len(matrix) - 1
    y = len(matrix) - 1
    combinedPath = ""

    while x > 0 or y > 0:
        direction = weightMatrixDir[y][x]
        combinedPath = direction + combinedPath
        if direction == 'D':
            y -= 1
        else:
            x -= 1

    return (weightMatrix2[len(matrix) - 1][len(matrix) - 1], \
            weightMatrix5[len(matrix) - 1][len(matrix) - 1]), combinedPath


# def weightAndPathBottomUp2(matrix, less):

#     width  = len(matrix[0])
#     height = len(matrix)

#     x,y = 0,0
#     currentWeight = numberWeight(matrix[0][0])
#     # weightMatrix2[0][0] = currentWeight[0]
#     # weightMatrix5[0][0] = currentWeight[1]
#     # weightMatrixDir[0][0] = ' '
#     path = ""

#     while (x, y) != (width-1, height-1):

#         # log("at: {} {}".format(x,y))

#         if x < width - 1:
#             rightStepWeight = numberWeight(matrix[y][x+1])

#         if y < height - 1:
#             downStepWeight  = numberWeight(matrix[y+1][x])

#         if x == width - 1:
#             currentWeight = sumWeight(currentWeight, downStepWeight)
#             path += 'D'
#             y += 1
#         elif y == height - 1:
#             currentWeight = sumWeight(currentWeight, rightStepWeight)
#             path += 'R'
#             x += 1
#         else:
#             if less(rightStepWeight, downStepWeight):
#                 currentWeight = sumWeight(currentWeight, rightStepWeight)
#                 path += 'R'
#                 x += 1
#             else:
#                 currentWeight = sumWeight(currentWeight, downStepWeight)
#                 path += 'D'
#                 y += 1

#     return currentWeight, path

# from guppy import hpy
# h = hpy()
# h.setref()



matrix = []

rowsCount = int(sys.stdin.readline())
for i in xrange(rowsCount):
    matrix.append(array('i', [int(x) for x in sys.stdin.readline().split()]))

# print "read"

# matrix = [[5, 5,  4,  10, 5,  5],
#           [7, 10, 8,  7,  6,  6],
#           [7, 1,  7,  9,  7,  8],
#           [5, 5,  3,  3,  10, 9],
#           [5, 8,  10, 6,  3,  8],
#           [3, 10, 5,  4,  3,  4]]

# matrix =[[8, 3, 2, 1, 4],
#          [3, 7, 2, 4, 8],
#          [9, 2, 8, 9, 10],
#          [2, 3, 6, 10, 1],
#          [8, 2, 2, 8, 4]]

# matrix = [[1, 2, 3],
#           [4, 5, 6],
#           [7, 8, 9]]

rowsCount = len(matrix[0])

weightAndPath2 = weightAndPathBottomUp(matrix, less2)
weightAndPath5 = weightAndPathBottomUp(matrix, less5)

# print weightAndPath2
# print weightAndPath5

# for y in xrange(len(matrix[0])):
#     for x in xrange(len(matrix[0])):
#         sys.stdout.write(str(weightMatrix2[y][x]))
#         sys.stdout.write(",")
#         sys.stdout.write(str(weightMatrix5[y][x]))
#         sys.stdout.write(" ")
#         sys.stdout.write(weightMatrixDir[y][x])
#         sys.stdout.write("  ")
#     sys.stdout.write('\n')

if min(weightAndPath2[0]) < min(weightAndPath5[0]):
    print min(weightAndPath2[0])
    print weightAndPath2[1]
else:
    print min(weightAndPath5[0])
    print weightAndPath5[1]

# print h.heap()