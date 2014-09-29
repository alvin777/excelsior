import sys
import random
from sets import Set


def getCarsPassengers(passengersList):
    if len(passengersList) == 1:
        return [passengersList[0],]

    subCarsPassengers = getCarsPassengers(passengersList[1:])

    print "subCarsPassengers:", subCarsPassengers, " len:", len(subCarsPassengers), " passengers:", passengersList[0]

    for i in xrange(len(subCarsPassengers)):
        carsPassengersProposal = subCarsPassengers[:]
        carsPassengersProposal[i] += passengersList[0]
        print "check {} car: {}".format(i, carsPassengersProposal)

        if subCarsPassengers[i] + passengersList[0] <= 4:
            subCarsPassengers[i] += passengersList[0]
            print "ok"
            return subCarsPassengers

    print "returning join: ", subCarsPassengers + [passengersList[0], ]
    return subCarsPassengers + [passengersList[0], ]


def check(passengersList):
    passengersByCars = getCarsPassengers(passengersList)
    print "Passengers: {}, passengers by cars: {}, cars count: {}".format(passengersList, passengersByCars, len(passengersByCars))

def generator(count):
    return [int(random.random() * 4)+1 for _ in xrange(count)]

def f(count):
    check(generator(count))


def getCarsPassengersIterative(passengersList):
    passengersByCarsList = []

    passengersList.sort(reverse=True)
    vacantCarIndices = Set()

    for currentPassengersCount in passengersList:
        passengersAllocatedInExistingCar = False

        # for i in xrange(len(passengersByCarsList)):
        for i in vacantCarIndices:
            if passengersByCarsList[i] == 4:
                continue

            if passengersByCarsList[i] + currentPassengersCount <= 4:
                passengersByCarsList[i] += currentPassengersCount
                passengersAllocatedInExistingCar = True
                if passengersByCarsList[i] == 4:
                    vacantCarIndices.remove(i)
                break

        if not passengersAllocatedInExistingCar:
            passengersByCarsList.append(currentPassengersCount)
            if currentPassengersCount != 4:
                vacantCarIndices.add(len(passengersByCarsList) - 1)

        # print "Current passengers:", currentPassengersCount, " cars:", passengersByCarsList

    return passengersByCarsList

def checkIterative(passengersList):
    passengersByCars = getCarsPassengersIterative(passengersList)
    # print "Passengers: {}, passengers by cars: {}, cars count: {}".format(passengersList, passengersByCars, len(passengersByCars))


def getCarsPassengers3(passengersList):
    passengersList.sort(reverse=True)

    left = 0
    right = len(passengersList) - 1

    carsCount = 0

    while left <= right:
        carsCount += 1
        currentPassengersCount = passengersList[left]
        left += 1
        if currentPassengersCount < 4:
            while (currentPassengersCount + passengersList[right] <= 4) and (left <= right):
                currentPassengersCount += passengersList[right]
                right -= 1

    return carsCount
        


# check((1,2,2))
# check([int(x) for x in "1 2 4 3 3".split(' ')])
# check([int(x) for x in "2 3 4 4 2 1 3 1".split(' ')])

# checkIterative([int(x) for x in "2 3 4 4 2 1 3 1".split(' ')])

# count = int(sys.stdin.readline())
# data = sys.stdin.readline()
# print len(getCarsPassengersIterative([int(x) for x in data.split()]))

# print generator(1000)

# def f2(count):
#     checkIterative(generator(count))

# import timeit
# print timeit.timeit('f(100)', "from __main__ import f", number=10)
# print timeit.timeit('f2(10000)', "from __main__ import f2", number=1)
# print timeit.timeit('getCarsPassengers3(generator(100000))', "from __main__ import *", number=1)

# import cProfile
# cProfile.run("f(1000)")

# print getCarsPassengers3([int(x) for x in "2 3 4 4 2 1 3 1".split(' ')])
