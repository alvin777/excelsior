#!/usr/bin/python

import sys
import unittest
import random


def random_generator(size):
    counter = 0
    while counter < size:
        counter += 1
        yield int(random.random()*sys.maxint)


# LOAD_FACTOR_THRESHOLD = 0.75
LOAD_FACTOR_THRESHOLD = 5

class HashMap:
    def __init__(self, allow_duplicates=True, initial_size=16):
        self.allow_duplicates = allow_duplicates
        self.hash_array_size = initial_size
        # self.hash_array = array.array('L', [0 for _ in xrange(self.hash_array_size)])
        self.hash_array = [None] * self.hash_array_size
        self.elements_count = 0
        self.load_factor = 0

    def calculate_hash(self, key):
        return hash(key)

    def __getitem__(self, key):
        key_hash = self.calculate_hash(key)
        key_index = key_hash % self.hash_array_size

        if self.hash_array[key_index] is None:
            return None

        found_list = [value for (stored_key, value) in
                      self.hash_array[key_index] if stored_key == key]

        if len(found_list) == 0:
            return None

        if len(found_list) == 1:
            return found_list[0]

        return found_list

    def __setitem__(self, key, value):
        key_hash = self.calculate_hash(key)
        key_index = key_hash % self.hash_array_size

        # print key, key_hash, self.hash_array_size, key_index

        linked_list = self.hash_array[key_index]

        if linked_list is None:
            self.hash_array[key_index] = [(key, value)]
            self.elements_count += 1
            self.load_factor = self.elements_count/self.hash_array_size
        else:

            if self.allow_duplicates:
                linked_list.append((key, value))
                self.elements_count += 1
                self.load_factor = self.elements_count/self.hash_array_size
            else:
                found_key = False
                for i in xrange(len(linked_list)):
                    if linked_list[i][0] == key:
                        linked_list[i] = (key, value)
                        found_key = True
                        break

                if not found_key:
                    linked_list.append((key, value))
                    self.elements_count += 1
                    self.load_factor = self.elements_count/self.hash_array_size

        if self.load_factor >= LOAD_FACTOR_THRESHOLD:
            self.resize(self.hash_array_size*2)

    def __delitem__(self, key):
        key_hash = self.calculate_hash(key)
        key_index = key_hash % self.hash_array_size

        if self.hash_array[key_index] is not None:
            list_len_before = len(self.hash_array[key_index])
            self.hash_array[key_index][:] = [(stored_key, value) for (stored_key, value)
                                            in self.hash_array[key_index] if not key == stored_key]
            list_len_after = len(self.hash_array[key_index])
            len_diff = list_len_before - list_len_after
            self.elements_count -= len_diff
            self.load_factor = self.elements_count/self.hash_array_size

    def size(self):
        return self.elements_count

    def resize(self, new_size):
        # print 'resizing to', new_size
        old_hash_array = self.hash_array

        self.hash_array = [None] * new_size
        self.hash_array_size = new_size
        self.elements_count = 0
        self.load_factor = 0

        for i in xrange(len(old_hash_array)):
            if old_hash_array[i] is not None:
                for j in xrange(len(old_hash_array[i])):
                    self[old_hash_array[i][j][0]] = old_hash_array[i][j][1]

    def stats(self):
        return [len(x) if x is not None else 0 for x in self.hash_array]


class TestSortingMethods(unittest.TestCase):
    def test_simple_hash_map(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[2] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[2], 20)

    def test_simple_collision(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[101] = 20

        self.assertEqual(hash_map.size(), 2)
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

        self.assertEqual(hash_map.size(), len(reference_dict))

        for (key, value) in reference_dict.iteritems():
            self.assertEqual(hash_map[key], value)

        # print hash_map.stats()

    def test_1000_elements_limited(self):
        hash_map = HashMap(allow_duplicates=False)
        reference_dict = {}

        for x in xrange(1000):
            key = int(random.random()*1000)
            value = int(random.random()*1000)
            reference_dict[key] = value
            hash_map[key] = value

        self.assertEqual(hash_map.size(), len(reference_dict))

        for (key, value) in reference_dict.iteritems():
            self.assertEqual(hash_map[key], value)

        # print hash_map.stats()

    def test_restrict_duplicates(self):
        hash_map = HashMap(allow_duplicates=False)
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 20)

    def test_deletion(self):
        hash_map = HashMap()
        hash_map[1] = 10
        hash_map[101] = 20
        del hash_map[101]

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

    def test_deletion_restrict_duplicates(self):
        hash_map = HashMap(allow_duplicates=False)
        hash_map[1] = 10
        hash_map[101] = 20
        hash_map[101] = 30
        del hash_map[101]

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

    def test_string_keys(self):
        hash_map = HashMap()
        hash_map['1'] = 10
        hash_map['2'] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map['1'], 10)
        self.assertEqual(hash_map['2'], 20)        

if __name__ == '__main__':
    unittest.main()
