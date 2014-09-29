from collections import Counter

# data = map(int, raw_input().split())

# m = {}
# for v in data:
#     if v in m.keys():
#         m[v] += 1
#     else:
#         m[v] = 1


m = Counter(map(int, raw_input().split()))

body = False
elephant_head = False
bear_head = False

for k,v in m.iteritems():
    if v in [4, 5]:
        body = True
    elif v == 2:
        elephant_head = True
    elif v == 6:
        body = True
        elephant_head = True

if body:
    if elephant_head:
        print "Elephant"
    else:
        print "Bear"
else:
    print "Alien"