import sys
inputLines = sys.stdin.read().splitlines()

for i in xrange(1, int(inputLines[0]) + 1):
    string = inputLines[i]

    if len(string) > 10:
        print string[0] + str(len(string) - 2) + string[len(string) - 1]
    else:
        print string