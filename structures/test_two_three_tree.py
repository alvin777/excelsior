import unittest
import logging
import random

class TwoThreeNode():
    def __init__(self, parent, key, left=None, right=None):
        self.parent = parent
        self.keys = [key]

        if left is not None and right is not None:
            self.children = [left, right]
            left.parent = right.parent = self
        else:
            self.children = []

    def __str__(self):
        return str(self.keys)[1:-1]

    def get_height(self):
        height = 0
        node = self
        while node:
            height += 1
            node = node.parent

        return height

    def get_child_for_key(self, key):
        if len(self.children) == 0:
            return None

        for i in xrange(len(self.keys)):
            if key < self.keys[i]:
                return self.children[i]

        return self.children[-1]

    def get_child_index_for_node(self, node):
        for i in xrange(len(self.children)):
            if self.children[i] == node:
                return i

        return None

    def insert_key_to_correct_pos(self, key):
        assert len(self.children) == 0

        if key > self.keys[-1]:
            self.keys.append(key)
        else:
            insert_pos = 0
            while insert_pos < len(self.keys) and key > self.keys[insert_pos]:
                insert_pos += 1

            self.keys.insert(insert_pos, key)

    def split_node(self):
        assert len(self.keys) == 3
        assert len(self.children) in [0, 4]

        children = [None]*4 if len(self.children) == 0 else self.children

        left = TwoThreeNode(self, self.keys[0], children[0], children[1])
        key = self.keys[1]
        right = TwoThreeNode(self, self.keys[2], children[2], children[3])
        return (key, left, right)

    def merge_node(self, key, left, right):

        # print 'merge_node self: {}, key: {}, left: {}, right: {}'.format(node, key, left, right)
        if key > self.keys[-1]:
            self.keys.append(key)
            self.children[-1] = left
            self.children.append(right)
        else:
            insert_pos = 0
            while insert_pos < len(self.keys) and key > self.keys[insert_pos]:
                insert_pos += 1

            self.keys.insert(insert_pos, key)
            self.children[insert_pos] = left
            self.children.insert(insert_pos+1, right)
            
        left.parent = self
        right.parent = self

    def is_leaf(self):
        return len(self.children) == 0

    def is_three_node(self):
        return len(self.keys) == 2

    def is_two_node(self):
        return len(self.keys) == 1

    def get_right_sibling(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return None

        if child_index == len(self.parent.children) - 1:
            return None

        return self.parent.children[child_index + 1]

    def get_left_sibling(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return None

        if child_index == 0:
            return None

        return self.parent.children[child_index - 1]

    def pop_last_key(self):
        if len(self.keys) == 0:
            return None

        return self.keys.pop()

    def pop_first_key(self):
        if len(self.keys) == 0:
            return None

        key = self.keys[0]
        self.keys = self.keys[1:]
        return key

    def pop_last_child(self):
        if len(self.children) == 0:
            return None

        return self.children.pop()

    def pop_first_child(self):
        if len(self.children) == 0:
            return None

        child = self.children[0]
        self.children = self.children[1:]
        return child

    def insert_key(self, key):
        self.keys.insert(0, key)

    def append_key(self, key):
        self.keys.append(key)

    def insert_child(self, child):
        if child is None:
            return

        self.children.insert(0, child)
        child.parent = self

    def append_child(self, child):
        if child is None:
            return

        self.children.append(child)
        child.parent = self

    def get_left_parent_key(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return None

        return self.parent.keys[child_index - 1]

    def get_right_parent_key(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return None

        return self.parent.keys[child_index]

    def set_left_parent_key(self, key):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return

        if key is None:
            self.parent.keys.pop(child_index - 1)
            self.parent.children.pop(child_index - 1)
        else:
            self.parent.keys[child_index - 1] = key

    def set_right_parent_key(self, key):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return

        if key is None:
            self.parent.keys.pop(child_index)
            self.parent.children.pop(child_index + 1)
        else:
            self.parent.keys[child_index] = key

    def remove_leaf_3_node_key(self, key):
        assert self.is_leaf()
        assert len(self.keys) >= 2
        assert key in self.keys

        for i in xrange(len(self.keys)):
            if self.keys[i] == key:
                self.keys.pop(i)
                break

    def _can_borrow_from_node_to_the_right(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return False

        for i in xrange(child_index + 1, len(self.parent.children)):
            if self.parent.children[i].is_three_node():
                return True

        return False

    def _can_borrow_from_node_to_the_left(self):
        child_index = self.parent.get_child_index_for_node(self)
        if child_index is None:
            return False

        for i in xrange(child_index - 1, -1, -1):
            if self.parent.children[i].is_three_node():
                return True

        return False

class TwoThreeTree:
    def __init__(self):
        self.root = None

    def breadth_first_search(self, f):
        stack = [self.root]

        while len(stack) > 0:
            node = stack.pop(0)
            f(node)
            stack.extend(node.children)

    def search(self, node, key):
        while node is not None:
            if key in node.keys:
                return (True, node)

            child_node = node.get_child_for_key(key)
            if child_node is None:
                return (False, node)

            node = child_node


    def insert(self, key):
        if self.root is None:
            self.root = TwoThreeNode(None, key)

        (found, target_node) = self.search(self.root, key)

        if found:
            return   # do not allow same values

        self.insert_key_to_correct_pos(target_node, key)

    def insert_key_to_correct_pos(self, node, key):
        node.insert_key_to_correct_pos(key)

        if len(node.keys) >= 3:
            self._fix_tree(node)

    def _fix_tree(self, node):
        # assert node has three keys

        (key, left, right) = node.split_node()

        # print '_fix_tree node: {}, key: {}, left: {}, right: {}'.format(node, key, left, right)

        if node.parent:
            node.parent.merge_node(key, left, right)
            if len(node.parent.keys) >= 3:
                self._fix_tree(node.parent)
        else:
            # root
            self.root = TwoThreeNode(None, key, left, right)

    def _rotate_right_while_empty_node(self, node):
        while len(node.keys) == 0:
            self._rotate_right(node)
            node = node.get_left_sibling()

    def _rotate_left_while_empty_node(self, node):
        while len(node.keys) == 0:
            self._rotate_left(node)
            node = node.get_right_sibling()

    def _rotate_left(self, node):
        sibling = node.get_right_sibling()

        logging.debug('_rotate_left, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        node.append_key(node.get_right_parent_key())
        node.set_right_parent_key(sibling.pop_first_key())
        node.append_child(sibling.pop_first_child())

        logging.debug('_rotate_left complete, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

    def _rotate_right(self, node):
        sibling = node.get_left_sibling()

        logging.debug('_rotate_right, node: (%s), parent: (%s), sibling: (%s)', \
            node, node.parent, sibling)

        node.insert_key(node.get_left_parent_key())
        node.set_left_parent_key(sibling.pop_last_key())
        node.insert_child(sibling.pop_last_child())

        logging.debug('_rotate_right complete, node: (%s), parent: (%s), sibling: (%s)', \
            node, node.parent, sibling)

    def _find_predessor(self, node, key):
        assert not node.is_leaf()

        for i in xrange(len(node.keys)):
            if node.keys[i] == key:
                left_child = node.children[i]
                break

        if left_child.is_leaf():
            return left_child

        rightmost_child = left_child.children[-1]
        while not rightmost_child.is_leaf():
            rightmost_child = rightmost_child.children[-1]

        return rightmost_child

    def _swap_keys(self, node, predessor, key):
        logging.debug('_swap_keys, node: (%s), predessor: (%s), key: (%s)', node, predessor, key)
        for i in xrange(len(node.keys)):
            if node.keys[i] == key:

                node.keys[i], predessor.keys[-1] = predessor.keys[-1], node.keys[i]
                break
        logging.debug('_swap_keys complete, node: (%s), predessor: (%s), key: (%s)', node, predessor, key)

    def remove(self, key):
        # find node
        # if not leaf - swap
        # fix empty node
        logging.debug('remove, key: %d', key)
        
        (found, node) = self.search(self.root, key)

        logging.debug('node to remove: (%s)', node)

        if not found:
            return

        if not node.is_leaf():
            predessor = self._find_predessor(node, key)
            logging.debug('predessor: (%s)', predessor)
            self._swap_keys(node, predessor, key)
            logging.debug('after swap, node: (%s), predessor: (%s)', node, predessor)
            node = predessor

        if node.is_three_node():
            node.remove_leaf_3_node_key(key)
            return

        node.pop_last_key()
        node.pop_last_child()

        self._remove_node(node)

    def _remove_node(self, node):

        if node == self.root and self.root.is_leaf():
            self.root = None
            return

        if node._can_borrow_from_node_to_the_right():
            self._rotate_left_while_empty_node(node)
        elif node._can_borrow_from_node_to_the_left():
            self._rotate_right_while_empty_node(node)
        else:
            if node.parent.is_two_node():
                if node.get_right_sibling() is not None:
                    self._rotate_left(node)
                    self._rotate_left(node)
                else:
                    self._rotate_right(node)
                    self._rotate_right(node)

                if node.parent == self.root:
                    self.root = node
                    node.parent = None
                else:
                    self._remove_node(node.parent)

            else:
                right_sibling = node.get_right_sibling()
                left_sibling  = node.get_left_sibling()

                if left_sibling is None:
                    self._rotate_left(node)
                    self._rotate_right(right_sibling.get_right_sibling())
                elif right_sibling is None:
                    self._rotate_right(node)
                    self._rotate_left(left_sibling.get_left_sibling())
                else:
                    self._rotate_right(right_sibling)


class TestTwoThreeTree(unittest.TestCase):

    def create_sequential_tree(self, count):
        tree = TwoThreeTree()

        for x in xrange(1, count+1):
            tree.insert(x)

        return tree

    def create_tree(self, range):
        tree = TwoThreeTree()

        for x in range:
            tree.insert(x)

        return tree
            
    def assert_node(self, node, keys, children_count):
        self.assertEquals(keys, node.keys)
        self.assertEquals(children_count, len(node.children))
        for i in xrange(len(node.children)):
            self.assertEquals(node, node.children[i].parent)

    def test_empty(self):
        tree = TwoThreeTree()
        self.assertEquals(None, tree.root)

    def test_1(self):
        tree = TwoThreeTree()
        tree.insert(1)
        self.assertEquals([1], tree.root.keys)
        self.assertEquals([], tree.root.children)

    def test_2(self):
        tree = TwoThreeTree()
        tree.insert(1)
        tree.insert(2)
        self.assertEquals([1,2], tree.root.keys)
        self.assertEquals([], tree.root.children)

    def test_3(self):
        tree = self.create_sequential_tree(3)

        self.assert_node(tree.root, [2], 2)
        self.assert_node(tree.root.children[0], [1], 0)
        self.assert_node(tree.root.children[1], [3], 0)

    def test_4(self):
        tree = self.create_sequential_tree(4)

        self.assert_node(tree.root, [2], 2)
        self.assert_node(tree.root.children[0], [1], 0)
        self.assert_node(tree.root.children[1], [3, 4], 0)
        
    def test_5(self):
        tree = self.create_sequential_tree(5)

        self.assert_node(tree.root, [2, 4], 3)
        self.assert_node(tree.root.children[0], [1], 0)
        self.assert_node(tree.root.children[1], [3], 0)
        self.assert_node(tree.root.children[2], [5], 0)

    def test_6(self):
        tree = self.create_sequential_tree(6)

        self.assert_node(tree.root, [2, 4], 3)
        self.assert_node(tree.root.children[0], [1], 0)
        self.assert_node(tree.root.children[1], [3], 0)
        self.assert_node(tree.root.children[2], [5, 6], 0)

    def test_7(self):
        tree = self.create_sequential_tree(7)

        self.assert_node(tree.root, [4], 2)
        self.assert_node(tree.root.children[0], [2], 2)
        self.assert_node(tree.root.children[1], [6], 2)
        self.assert_node(tree.root.children[0].children[0], [1], 0)
        self.assert_node(tree.root.children[0].children[1], [3], 0)
        self.assert_node(tree.root.children[1].children[0], [5], 0)
        self.assert_node(tree.root.children[1].children[1], [7], 0)


    #
    # Deletion
    #

    # near 3-siblings
    def test_del_3_sibling_2_parent_left(self):
        tree = self.create_sequential_tree(4)   #    2
                                                #  1   3,4
        tree.remove(1)

        self.assert_node(tree.root, [3], 2)                #   3
        self.assert_node(tree.root.children[0], [2], 0)    # 2   4
        self.assert_node(tree.root.children[1], [4], 0)    

    def test_del_3_sibling_2_parent_right(self):
        tree = self.create_sequential_tree(3)   #     2
        tree.insert(0)                          #  0,1   3

        tree.remove(3)

        self.assert_node(tree.root, [1], 2)
        self.assert_node(tree.root.children[0], [0], 0)
        self.assert_node(tree.root.children[1], [2], 0)

    def test_del_3_sibling_3_parent_left(self):
        tree = self.create_tree(xrange(0, 50, 10))  #    10,30
        tree.insert(25)                             # 0  20,25  40

        tree.remove(0)

        self.assert_node(tree.root, [20, 30], 3)              #     20,30 
        self.assert_node(tree.root.children[0], [10], 0)      # 10    25   40
        self.assert_node(tree.root.children[1], [25], 0)
        self.assert_node(tree.root.children[2], [40], 0)

    def test_del_3_sibling_3_parent_right(self):
        tree = self.create_tree(xrange(0, 50, 10))  #    10,30
        tree.insert(25)                             # 0  20,25  40

        tree.remove(40)

        self.assert_node(tree.root, [10, 25], 3)           #   10,25
        self.assert_node(tree.root.children[0], [0], 0)    # 0   20   30
        self.assert_node(tree.root.children[1], [20], 0)
        self.assert_node(tree.root.children[2], [30], 0)

    def test_del_3_sibling_3_parent_center_right(self):
        tree = self.create_sequential_tree(6)   #    2,4
                                                #  1  3  5,6
        tree.remove(3)

        self.assert_node(tree.root, [2,5], 3)
        self.assert_node(tree.root.children[0], [1], 0)
        self.assert_node(tree.root.children[1], [4], 0)
        self.assert_node(tree.root.children[2], [6], 0)

    def test_del_3_sibling_3_parent_center_left(self):
        tree = self.create_sequential_tree(5)   #     2,4
                                                #  0,1  3  5

        tree.insert(0)
        tree.remove(3)

        self.assert_node(tree.root, [1,4], 3)
        self.assert_node(tree.root.children[0], [0], 0)
        self.assert_node(tree.root.children[1], [2], 0)
        self.assert_node(tree.root.children[2], [5], 0)

    # far 3-siblings
    def test_del_3_far_sibling_3_parent_right(self):
        tree = self.create_tree(xrange(0, 50, 10))  #   10,30
        tree.insert(45)                             # 0  20  40,45
        tree.remove(0)

        self.assert_node(tree.root, [20, 40], 3)          #    20,40
        self.assert_node(tree.root.children[0], [10], 0)  # 10  30  45
        self.assert_node(tree.root.children[1], [30], 0)
        self.assert_node(tree.root.children[2], [45], 0)

    def test_del_3_far_sibling_3_parent_left(self):
        tree = self.create_tree(xrange(0, 50, 10))  #    10,30
        tree.insert(5)                              # 0,5  20  40
        tree.remove(40)

        self.assert_node(tree.root, [5, 20], 3)           #   5,20
        self.assert_node(tree.root.children[0], [0],  0)  # 0  10  30
        self.assert_node(tree.root.children[1], [10], 0)
        self.assert_node(tree.root.children[2], [30], 0)

    # 2-sibling, 3-parent
    def test_del_2_sibling_3_parent_left(self):
        tree = self.create_sequential_tree(5)   #    2,4
                                                #  1  3  5
        tree.remove(1)

        self.assert_node(tree.root, [3], 2)               #   3
        self.assert_node(tree.root.children[0], [2],  0)  # 2  4,5
        self.assert_node(tree.root.children[1], [4, 5], 0)

    def test_del_2_sibling_3_parent_center(self):
        tree = self.create_sequential_tree(5)   #    2,4
                                                #  1  3  5
        tree.remove(3)

        self.assert_node(tree.root, [2], 2)               #   2
        self.assert_node(tree.root.children[0], [1],  0)  # 1  4,5
        self.assert_node(tree.root.children[1], [4, 5], 0)

    def test_del_2_sibling_3_parent_right(self):
        tree = self.create_sequential_tree(5)   #    2,4
                                                #  1  3  5
        tree.remove(5)

        self.assert_node(tree.root, [3], 2)                  #    3
        self.assert_node(tree.root.children[0], [1, 2],  0)  # 1,2  4
        self.assert_node(tree.root.children[1], [4], 0)

    # 2-sibling, 2-parent
    def test_del_2_sibling_2_parent_rec(self):
        tree = self.create_sequential_tree(7)  #      4
                                               #   2     6
                                               # 1  3   5  7
        tree.remove(7)

        self.assert_node(tree.root, [2, 4], 3)               #   2,4
        self.assert_node(tree.root.children[0], [1], 0)      # 1  3  5,6
        self.assert_node(tree.root.children[1], [3], 0)
        self.assert_node(tree.root.children[2], [5, 6], 0)

    def test_del_non_leaf(self):
        tree = self.create_sequential_tree(7)  #      4
                                               #   2     6
                                               # 1  3   5  7
        tree.remove(6)

        self.assert_node(tree.root, [2, 4], 3)               #   2,4
        self.assert_node(tree.root.children[0], [1], 0)      # 1  3  5,7
        self.assert_node(tree.root.children[1], [3], 0)
        self.assert_node(tree.root.children[2], [5, 7], 0)

    def assert_two_three_node(self, tree, node):
        self.assertIn(len(node.keys), [1, 2])

        if len(node.keys) == 2:
            self.assertTrue(node.keys[0] < node.keys[1])

        if node.is_leaf():
            if self.tree_height is None:
                self.tree_height = node.get_height()
            else:
                self.assertEquals(self.tree_height, node.get_height())
        else:
            self.assertTrue(node.children[0].keys[-1] < node.keys[0])
            self.assertTrue(node.children[1].keys[0]  > node.keys[0])

            if len(node.keys) == 1:
                self.assertEquals(len(node.children), 2)

            if len(node.keys) == 2:
                self.assertEquals(len(node.children), 3)
                self.assertTrue(node.children[1].keys[-1] < node.keys[1])
                self.assertTrue(node.children[2].keys[0]  > node.keys[1])

            for child in node.children:
                self.assertEquals(child.parent, node)

    def test_bfs(self):
        tree = self.create_sequential_tree(7)  #      4
                                               #   2     6
                                               # 1  3   5  7
        self.tree_height = None

        tree.breadth_first_search(lambda node: self.assert_two_three_node(tree, node))

        def print_node(node):
            logging.debug('%s', node)

        tree.breadth_first_search(print_node)

    def test_random_data(self):
        tree = TwoThreeTree()
        reference_list = []

        for i in xrange(1000):
            if (len(reference_list) == 0) or (random.random() >= 0.25):
                new_value = random.randint(0, 2**30)
                logging.debug("inserting value: %d", new_value)

                tree.insert(new_value)
                reference_list.append(new_value)
            else:
                value_index_to_delete = random.randint(0, len(reference_list) - 1)
                value_to_delete = reference_list[value_index_to_delete]
                logging.debug("deleting value: %d", value_to_delete)

                tree.remove(value_to_delete)
                reference_list.pop(value_index_to_delete)

        self.tree_height = None
        tree.breadth_first_search(lambda node: self.assert_two_three_node(tree, node))

        tree_list = []
        tree.breadth_first_search(lambda node: tree_list.extend(node.keys))

        self.assertEquals(sorted(reference_list), sorted(tree_list))


# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.DEBUG)
# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.INFO)
