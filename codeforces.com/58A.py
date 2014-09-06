
HELLO_STRING = "hello"

def isHello(line):
    helloIndex = 0
    lineIndex = 0
    while lineIndex < len(line):
        while lineIndex < len(line) and line[lineIndex] != HELLO_STRING[helloIndex]:
            # print line[lineIndex]
            lineIndex += 1

        if lineIndex < len(line):
            # print ">>", line[lineIndex]
            helloIndex += 1

        lineIndex += 1

        if helloIndex >= len(HELLO_STRING):
            return True

    return False

# print isHello("xqjqmenkodmlhzyzmmvofdngktygbbxbzpluzcohohmalkoeuwfikblltaaigv")
# print isHello("hlelo")

if isHello(raw_input()):
    print "YES"
else:
    print "NO"