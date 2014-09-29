a = [int(x) for x in input().split()[1:]]
q = [int(x) for x in input().split()[1:]]

m = {}
for i in range(len(a)):
    m[a[i]] = i

for i in range(len(q)):
    if q[i] in m:
        print(m[q[i]] + 1, '', end='')
    else:
        print("-1", '', end='');

print()