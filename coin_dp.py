
nominalsList = [1,2,5,10]

coinsCountAndNominals = {}

def getCoinsCount(sum):
    if sum == 0:
        return 0, ()

    if sum in coinsCountAndNominals:
        return coinsCountAndNominals[sum]

    minCount = 10000
    for currentNominal in nominalsList:
        if sum < currentNominal: 
            continue

        currentCount, subNominals = getCoinsCount(sum - currentNominal)
        if currentCount + 1 < minCount:
            minCount = currentCount + 1
            nominals = subNominals + (currentNominal,)

    coinsCountAndNominals[sum] = (minCount, nominals)
    return coinsCountAndNominals[sum]


for i in xrange(1, 100 + 1):
    coinsCount, nominalsList2 = getCoinsCount(i)
    print "i: {}, solution: {} {}".format(i, coinsCount, nominalsList2)