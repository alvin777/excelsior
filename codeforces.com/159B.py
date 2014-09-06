import sys

def closeMarkers(markersArray, capsArray):
    closedMarkers = 0
    beautifullyClosedMarkers = 0

    for size in xrange(1000):
        notClosedMarkers = 0
        unusedCaps = 0
        for color in xrange(1000):
            # print "size:", size, "color:", color

            while markersArray[size][color] > 0 and capsArray[size][color] > 0:
                beautifullyClosedMarkers += 1
                markersArray[size][color] -= 1
                capsArray[size][color] -= 1


            notClosedMarkers += markersArray[size][color]
            unusedCaps += capsArray[size][color]

        closedMarkers += min(notClosedMarkers, unusedCaps)

    return closedMarkers+beautifullyClosedMarkers, beautifullyClosedMarkers

markersCount, capsCount = [int(x) for x in sys.stdin.readline().split()]

markersArray = [[0 for _ in xrange(1000)] for _ in xrange(1000)]
capsArray    = [[0 for _ in xrange(1000)] for _ in xrange(1000)]

for i in xrange(markersCount):
    markerColor, markerSize = [int(x)-1 for x in sys.stdin.readline().split()]
    # print "markerColor, markerSize:", markerColor, markerSize
    markersArray[markerSize][markerColor] += 1

for i in xrange(capsCount):
    capColor, capSize = [int(x)-1 for x in sys.stdin.readline().split()]
    if capsArray[capSize] is None:
        capsArray[capSize] = {}
    capsArray[capSize][capColor] += 1

# for i in xrange(1000):
#     for j in xrange(1000):
#         if capsArray[i][j] > 0:
#             print "size: ", i, "color:", j

closedMarkers, beautifullyClosedMarkers = closeMarkers(markersArray, capsArray)
print closedMarkers, beautifullyClosedMarkers