#!/bin/python


def calc_max_change(data, money):
    max_change = -1

    # print "given money: {}".format(money*100)

    for dollars, cents in data:
        # print "checking {}".format(dollars*100 + cents)
        current_money = money * 100

        if current_money < dollars*100 + cents:
            # print "too expensive"
            continue

        # change = (current_money % (dollars*100 + cents)) % 100
        change = (100 - cents) % 100
        max_change = max(change, max_change)

        # print "cents change: {}".format(change)
    
    return max_change

count, dollars = map(int, raw_input().strip().split())
data = []
for i in xrange(count):
    data.append(map(int, raw_input().strip().split()))

# data = ((3, 90), (12, 0), (9, 70), (5, 50), (7, 0))
print calc_max_change(data, dollars)