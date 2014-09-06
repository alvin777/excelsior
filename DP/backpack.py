#!/bin/python

import logging
import unittest

WEIGHT = 0
VALUE = 1
ITEMS_LIST = 2


def calc_items_to_take(items_list, weight):

    weight_list = [] # (weight, value, items_list)

    for current_weight in xrange(0, weight+1):
        total_weight = 0
        total_value = 0
        taken_items_list = []
        max_total_value = 0

        logging.debug("current_weight: %d", current_weight)

        for item in items_list:
            logging.debug("  item: %s", item)

            item_weight = item[0]
            item_value = item[1]

            if item_weight > current_weight:
                logging.debug("    skipping")
                continue

            weight_list_record = weight_list[current_weight - item_weight]

            total_value = item_value + weight_list_record[VALUE]
            if total_value > max_total_value:
                max_total_value  = total_value
                total_weight = weight_list_record[WEIGHT] + item_weight
                taken_items_list = weight_list_record[ITEMS_LIST] + [item]
                logging.debug("    choosing, max_total_value: %d, total_weight: %d, taken_items_list: %s", max_total_value, total_weight, taken_items_list)

        weight_list.append((total_weight, max_total_value, taken_items_list))

    return weight_list[weight]

def calc_value(items_list, weight):
    m = [0 for _ in xrange(weight + 1)]
    keep = [[0 for _ in xrange(len(items_list))] for _ in xrange(weight+1)]

    print "\n".join(map(str,keep))

    for w in xrange(1, weight + 1):
        # m[w] = max([m[w-1]] + [item[VALUE] + m[w - item[WEIGHT]] for item in items_list if item[WEIGHT] <= w])
        for i in xrange(len(items_list)):
            item = items_list[i]
            if item[WEIGHT] <= w and item[VALUE] + m[w - item[WEIGHT]] > m[w]:
                m[w] = item[VALUE] + m[w - item[WEIGHT]]
                keep[w] = keep[w - item[WEIGHT]]
                keep[w][i] += 1


    logging.debug("%s", m)
    print "\n".join(map(str,keep))

    return m[weight]


class TestBackpack(unittest.TestCase):
    # def test_simple(self):
    #     items_list = ((10, 60), 
    #                   (20, 130),
    #                   (30, 120))

    #     weight_list = calc_items_to_take(items_list, 100)
    #     print weight_list


    def test_simple2(self):
        items_list = ((10, 60), 
                      (20, 130),
                      (30, 120))

        value = calc_value(items_list, 100)
        print value


logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.DEBUG)

if __name__ == '__main__':
    unittest.main()

