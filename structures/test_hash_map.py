#!/usr/bin/python

import sys
import unittest
import random


def random_generator(size):
    counter = 0
    while counter < size:
        counter += 1
        yield int(random.random()*sys.maxint)


class ChainedHashMap:
    def __init__(self, allow_duplicates=False, initial_size=16, load_factor_threshold=5):
        self.allow_duplicates = allow_duplicates
        self.hash_array_size = initial_size
        # self.hash_array = array.array('L', [0 for _ in xrange(self.hash_array_size)])
        self.hash_array = [None] * self.hash_array_size
        self.elements_count = 0
        self.load_factor = 0
        self.load_factor_threshold = load_factor_threshold

    def calculate_hash(self, key):
        return hash(key)

    def __getitem__(self, key):
        key_hash = self.calculate_hash(key)
        key_index = key_hash % self.hash_array_size

        if self.hash_array[key_index] is None:
            return None

        found_list = [value for (stored_key, value) in
                      self.hash_array[key_index] if stored_key == key]

        if not self.allow_duplicates:
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
            found_key = False
            if not self.allow_duplicates:
                for i in xrange(len(linked_list)):
                    if linked_list[i][0] == key:
                        linked_list[i] = (key, value)
                        found_key = True
                        break

            if self.allow_duplicates or not found_key:
                linked_list.append((key, value))
                self.elements_count += 1
                self.load_factor = self.elements_count/self.hash_array_size

        if self.load_factor >= self.load_factor_threshold:
            self.resize(self.hash_array_size*2)

    def __delitem__(self, key):
        key_hash = self.calculate_hash(key)
        key_index = key_hash % self.hash_array_size
        linked_list = self.hash_array[key_index]

        if linked_list is not None:
            list_len_before = len(linked_list)
            linked_list[:] = [(stored_key, value) for (stored_key, value) in linked_list if not key == stored_key]
            len_diff = list_len_before - len(linked_list)

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

        for linked_list in [x for x in old_hash_array if x is not None]:
            for (key, value) in linked_list:
                self[key] = value

    def stats(self):
        return [len(x) if x is not None else 0 for x in self.hash_array]


class OpenAddressingHashMap:
    def __init__(self, allow_duplicates=False, initial_size=16, load_factor_threshold=0.75):
        self.allow_duplicates = allow_duplicates
        self.hash_array_size = initial_size
        # self.hash_array = array.array('L', [0 for _ in xrange(self.hash_array_size)])
        self.hash_array = [None] * self.hash_array_size
        self.elements_count = 0
        self.load_factor = 0
        self.load_factor_threshold = load_factor_threshold

        self.deletedValueStub = ()

    def calculate_hash(self, key):
        return hash(key)

    def __getitem__(self, key):
        key_hash = self.calculate_hash(key)
        initial_key_index = key_hash % self.hash_array_size

        key_index = initial_key_index
        resultsList = []
        while True:
            if self.hash_array[key_index] is None:
                break

            if self.hash_array[key_index] is not self.deletedValueStub and self.hash_array[key_index][0] == key:
                if self.allow_duplicates:
                    resultsList.append(self.hash_array[key_index][1])
                else:
                    return self.hash_array[key_index][1]

            key_index += 1
            key_index %= self.hash_array_size

            if key_index == initial_key_index:   # do .. while key_index != initial_key_index
                break

        if self.allow_duplicates:
            return resultsList

        return None

    def __setitem__(self, key, value):
        key_hash = self.calculate_hash(key)
        initial_key_index = key_hash % self.hash_array_size

        # print 'setitem:', key, key_hash, self.hash_array_size, initial_key_index

        key_index = initial_key_index
        inserted = False
        while True:
            # print 'key_index:', key_index, 'initial_key_index:', initial_key_index, 'self.hash_array_size:', self.hash_array_size, \
                  # 'self.hash_array:', self.hash_array

            if self.hash_array[key_index] is None or self.hash_array[key_index] is self.deletedValueStub:
                self.hash_array[key_index] = (key, value)
                inserted = True
                break
            elif not self.allow_duplicates and self.hash_array[key_index][0] == key:
                self.hash_array[key_index] = (key, value)
                break

            key_index += 1
            key_index %= self.hash_array_size
            if key_index == initial_key_index:
                raise Exception("No more space")

        if inserted:
            self.elements_count += 1
            self.load_factor = self.elements_count/self.hash_array_size

            if self.load_factor >= self.load_factor_threshold:
                self.resize(self.hash_array_size*2)

    def __delitem__(self, key):
        key_hash = self.calculate_hash(key)
        initial_key_index = key_hash % self.hash_array_size

        key_index = initial_key_index
        deleted = False

        while True:
            # print 'key_index:', key_index, 'self.hash_array[key_index]:', self.hash_array[key_index]

            if self.hash_array[key_index] is None:
                break

            if self.hash_array[key_index] is not self.deletedValueStub and self.hash_array[key_index][0] == key:
                self.hash_array[key_index] = self.deletedValueStub

                self.elements_count -= 1

                if not self.allow_duplicates:
                    break

            key_index += 1
            key_index %= self.hash_array_size

            if key_index == initial_key_index:   # one loop is enough
                break

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

        for (key, value) in [(key, value) for (key, value) in old_hash_array if (key, value) is not None]:
            self[key] = value

    # def stats(self):
    #     return [len(x) if x is not None else 0 for x in self.hash_array]


class TestChainedHashMap(unittest.TestCase):
    def test_simple_hash_map(self):
        hash_map = ChainedHashMap()
        hash_map[1] = 10
        hash_map[2] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[2], 20)
        self.assertEqual(hash_map[3], None)
        self.assertEqual(hash_map[17], None)

    def test_simple_collision(self):
        hash_map = ChainedHashMap(initial_size=100)
        hash_map[1] = 10
        hash_map[101] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], 20)

    def test_1000_elements(self):
        hash_map = ChainedHashMap()
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
        hash_map = ChainedHashMap()
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
        hash_map = ChainedHashMap()
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 20)

    def test_deletion(self):
        hash_map = ChainedHashMap()
        hash_map[1] = 10
        hash_map[101] = 20
        del hash_map[101]

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

    def test_deletion_restrict_duplicates(self):
        hash_map = ChainedHashMap()
        hash_map[1] = 10
        hash_map[101] = 20
        hash_map[101] = 30
        del hash_map[101]

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], None)

    def test_string_keys(self):
        hash_map = ChainedHashMap()
        hash_map['1'] = 10
        hash_map['2'] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map['1'], 10)
        self.assertEqual(hash_map['2'], 20)

    def test_duplicates(self):
        hash_map = ChainedHashMap(allow_duplicates=True)
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], [10, 20])
        self.assertEqual(hash_map[2], None)


class TestOpenAddressingHashMap(unittest.TestCase):
    def test_simple_hash_map(self):
        hash_map = OpenAddressingHashMap()
        hash_map[1] = 10
        hash_map[2] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[2], 20)
        self.assertEqual(hash_map[3], None)
        self.assertEqual(hash_map[17], None)

    def test_simple_collision(self):
        hash_map = OpenAddressingHashMap(initial_size=100)
        hash_map[1] = 10
        hash_map[101] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[101], 20)

    def test_1000_elements(self):
        hash_map = OpenAddressingHashMap()
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
        hash_map = OpenAddressingHashMap()
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

    def test_allow_duplicates(self):
        hash_map = OpenAddressingHashMap(allow_duplicates=True)
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], [10, 20])
        self.assertEqual(hash_map[2], [])

    def test_deletion(self):
        hash_map = OpenAddressingHashMap(initial_size=100)
        hash_map[1] = 10
        hash_map[101] = 20
        del hash_map[101]

        self.assertEqual(hash_map.size(), 1)
        self.assertEqual(hash_map[1], 10)
        self.assertEqual(hash_map[2], None)
        self.assertEqual(hash_map[101], None)

    def test_deletion_allow_duplicates(self):
        hash_map = OpenAddressingHashMap(initial_size=100, allow_duplicates=True)
        hash_map[1] = 10
        hash_map[2] = 20
        hash_map[1] = 30
        hash_map[2] = 40
        del hash_map[2]
        hash_map[1] = 50

        self.assertEqual(hash_map.size(), 3)
        self.assertEqual(hash_map[1], [10, 50, 30])
        self.assertEqual(hash_map[2], [])
        self.assertEqual(hash_map[101], [])
        self.assertEqual(hash_map[102], [])

        # print hash_map.hash_array

    def test_string_keys(self):
        hash_map = OpenAddressingHashMap()
        hash_map['1'] = 10
        hash_map['2'] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map['1'], 10)
        self.assertEqual(hash_map['2'], 20)

    def test_duplicates(self):
        hash_map = OpenAddressingHashMap(allow_duplicates=True)
        hash_map[1] = 10
        hash_map[1] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[1], [10, 20])
        self.assertEqual(hash_map[2], [])

    def test_overflow(self):
        hash_map = OpenAddressingHashMap(initial_size=16)
        hash_map[15] = 10
        hash_map[16] = 20

        self.assertEqual(hash_map.size(), 2)
        self.assertEqual(hash_map[15], 10)
        self.assertEqual(hash_map[16], 20)

        # print hash_map.hash_array


# if __name__ == '__main__':
#     unittest.main()
