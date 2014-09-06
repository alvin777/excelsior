import sys


# def calcMinThickness(booksList):
#     totalVerticalThickness   = sum((book[0] for book in booksList))
#     totalHorizontalThickness = 0

#     while True:
#         bookToTry = booksList[-1]
#         newTotalVerticalThickness   = totalVerticalThickness   - bookToTry[0]
#         newTotalHorizontalThickness = totalHorizontalThickness + bookToTry[1]

#         print "book: ", bookToTry
#         print "totalVerticalThickness: ", totalVerticalThickness, " totalHorizontalThickness: ", totalHorizontalThickness
#         print "newTotalVerticalThickness: ", newTotalVerticalThickness, " newTotalHorizontalThickness: ", newTotalHorizontalThickness

#         if max(newTotalHorizontalThickness, newTotalVerticalThickness) > max(totalVerticalThickness, totalHorizontalThickness):
#             return max(totalVerticalThickness, totalHorizontalThickness)

#         booksList = booksList[:-1]
#         totalVerticalThickness = newTotalVerticalThickness
#         totalHorizontalThickness = newTotalHorizontalThickness


# def calcMinThicknessGreedy(booksList):
#     totalVerticalThickness = 0
#     totalHorizontalThickness = 0
#     for book in booksList:
#         print "book: ", book
#         if totalVerticalThickness == totalHorizontalThickness:
#             if book[0] <= book[1]:
#                 totalVerticalThickness   += book[0]
#             else:
#                 totalHorizontalThickness += book[1]
#         elif totalVerticalThickness < totalHorizontalThickness:
#             totalVerticalThickness   += book[0]
#         else:
#             totalHorizontalThickness += book[1]

#         print "totalHorizontalThickness:", totalHorizontalThickness, "totalVerticalThickness:", totalVerticalThickness
#     return max(totalVerticalThickness, totalHorizontalThickness)

def l(*argsList):
    # return 
    sys.stdout.write(" " * (indent - 1)*1)
    for arg in argsList:
        sys.stdout.write(str(arg))
        sys.stdout.write(" ")
    sys.stdout.write("\n")    

indent = 0
def indentWrapper(func):
    def indentFunc(*args):
        global indent
        
        indent += 1
        l(">>", *args[1:])
        ret = func(*args)
        l("<<", ret)
        indent -= 1
        

        return ret
    return indentFunc

# @indentWrapper
# def calcMinThickness(booksList, index, thicknessVertical, thicknessHorizontal, maxThickness):

#     l("calcMinThickness: {} {} {} {}".format(index, thicknessVertical, thicknessHorizontal, maxThickness))

#     if max(thicknessVertical, thicknessHorizontal) + (len(booksList) - index)/2 > maxThickness:
#         return maxThickness

#     if index >= len(booksList):
#         return max(thicknessVertical, thicknessHorizontal)

#     # vertical case
#     newThicknessVertical    = thicknessVertical + booksList[index][0]    
#     thicknessBookVertical   = calcMinThickness(booksList, index + 1, newThicknessVertical, thicknessHorizontal, maxThickness)
#     maxThickness = min(maxThickness, thicknessBookVertical)

#     # horizontal case
#     newThicknessHorizontal  = thicknessHorizontal + booksList[index][1]
#     thicknessBookHorizontal = calcMinThickness(booksList, index + 1, thicknessVertical, newThicknessHorizontal, maxThickness)
#     maxThickness = min(maxThickness, thicknessBookHorizontal)
#     l("<<", maxThickness)
#     return maxThickness

@indentWrapper
def calcMinThickness2(booksList, index, thicknessVertical, thicknessHorizontal, maxThickness):

    if index >= len(booksList):
        return max(thicknessVertical, thicknessHorizontal)

    # if thicknessHorizontal + (len(booksList) - index - 1)/2 >= maxThickness:
    #     return maxThickness
    if thicknessHorizontal >= maxThickness or thicknessHorizontal > thicknessVertical:
        return maxThickness

    if thicknessVertical == thicknessHorizontal:
        # print thicknessVertical
        # exit(0)
        return thicknessVertical

    t = booksList[index][0]
    w = booksList[index][1]

    maxThickness = min(maxThickness, thicknessVertical)

    thicknessIfHorizontal = calcMinThickness2(booksList, index + 1, thicknessVertical - t, thicknessHorizontal + w, maxThickness)
    maxThickness = min(maxThickness, thicknessIfHorizontal)
    thicknessIfVertical   = calcMinThickness2(booksList, index + 1, thicknessVertical,     thicknessHorizontal,     maxThickness)
    maxThickness = min(maxThickness, thicknessIfVertical)

    return maxThickness


count = int(sys.stdin.readline())

booksList = []
for i in xrange(count):
    t, w = (int(x) for x in sys.stdin.readline().split())
    booksList.append((t,w));

booksList.sort(key=lambda book:float(book[0])/book[1], reverse=True)
# print booksList
# print [sum(x) for x in zip(*booksList)]
# print min([sum(x) for x in zip(*booksList)])
sumVertical, sumHorizontal = [sum(x) for x in zip(*booksList)]
# print sumVertical, sumHorizontal

# print calcMinThicknessGreedy(booksList)
# print calcMinThickness(booksList, 0, 0, 0, min(sumVertical, sumHorizontal))
print calcMinThickness2(booksList, 0, sumVertical, 0, min(sumVertical, sumHorizontal))
# print calcMinThicknessGreedy(booksList)
