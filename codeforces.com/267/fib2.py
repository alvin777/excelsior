import collections

# n = int(input())
n = 11527523930876953
f = collections.deque([1, 1])
for i in range(2, n):
    f.append((f[0] + f[1]) % 26673)
    f.popleft()

print(f[-1])
