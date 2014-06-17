#!/usr/bin/python

import sys
import unittest
import random


def random_generator(size):
    counter = 0
    while counter < size:
        counter += 1
        yield int(random.random()*sys.maxint)


class HashMap:
    def __init__(self, allow_duplicates=True):
        self.allow_duplicates = allow_duplicates
        self.hash_array_length = 100
        # self.hash_array = array.array('L', [0 for _ in xrange(self.hash_array_length)])
        self.hash_array = [None] * self.hash_array_length
        self.size = 0

    def calculate_hash(self, key):
        return key % self.hash_array_length

    def __getitem__(self, key):
        key_hash = self.calculate_hash(key)

        if self.hash_array[key_hash] is None:
            return None

        found_list = [value for (stored_key, value) in
                      self.hash_array[key_hash] if stored_key == key]

        if len(found_list) == 0:
            return None

        if len(found_list) == 1:
            return found_list[0]

        return found_list

    def __setitem__(self, key, value):
        key_hash = self.calculate_hash(key)

        linked_list = self.hash_array[key_hash]

        if linked_list is None:
            self.hash_array[key_hash] = [(key, value)]
            self.size += 1
        else:

            if self.allow_duplicates:
                linked_list.append((key, value))
                self.size += 1
            else:
                found_key = False
                for i in xrange(len(linked_list)):
                    if linked_list[i][0] == key:
                        linked_list[i] = (key, value)
                        found_key = True
                        break

                if not found_key:
                    linked_list.append((key, value))
                    self.size += 1

    def __delitem__(self, key):
        key_hash = self.calculate_hash(key)

        if self.hash_array[key_hash] is not None:
            list_len_before = len(self.hash_array[key_hash])
            self.hash_array[key_hash][:] = [(stored_key, value) for (stored_key, value)
                                            in self.hash_array[key_hash] if not key == stored_key]
            list_len_after = len(self.hash_array[key_hash])
            len_diff = list_len_before - list_len_after
            self.size -= len_diff

    def size(self):
        return self.size


class TestSortingMethods(unittest.TestCase):
    def test_simple_hash_map(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[2] = 20

        self.assertEqual(hash_map.size, 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[2], 20)

    def test_simple_collision(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[101] = 20

        self.assertEqual(hash_map.size, 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], 20)

    def test_1000_elements(self):
        hash_map = HashMap()
        reference_dict = {}

        for x in xrange(1000):
            key = int(random.random()*sys.maxint)
            value = int(random.random()*sys.maxint)
            reference_dict[key] = value
            hash_map[key] = value

        self.assertEqual(hash_map.size, len(reference_dict))

        for (key, value) in reference_dict.iteritems():
            self.assertEqual(hash_map[key], value)

    def test_1000_elements_limited(self):
        hash_map = HashMap(allow_duplicates=False)
        reference_dict = {}

        for x in xrange(1000):
            key = int(random.random()*1000)
            value = int(random.random()*1000)
            reference_dict[key] = value
            hash_map[key] = value

        self.assertEqual(hash_map.size, len(reference_dict))

        for (key, value) in reference_dict.iteritems():
            self.assertEqual(hash_map[key], value)

    def test_restrict_duplicates(self):
        hash_map = HashMap(allow_duplicates=False)
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size, 1)
        self.assertEqual(hash_map[1], 20)

    def test_deletion(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[101] = 20
        del hash_map[101]

        self.assertEqual(hash_map.size, 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

    def test_deletion_restrict_duplicates(self):
        hash_map = HashMap(allow_duplicates=False)
        hash_map[1] = 10
        hash_map[101] = 20
        hash_map[101] = 30
        del hash_map[101]

        self.assertEqual(hash_map.size, 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

if __name__ == '__main__':
    unittest.main()
