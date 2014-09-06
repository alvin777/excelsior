import sys

vowels = ['a', 'o', 'u', 'e', 'i', 'y']

for char in raw_input():
    if char.lower() not in vowels:
        sys.stdout.write('.' + char.lower())