import unittest
import logging
import random

ROOT   = 10
RIGHT  = 11
CENTER = 12
LEFT   = 13

NEAR_3_NODE_LEFT  = 20
NEAR_3_NODE_RIGHT = 21
FAR_3_NODE_LEFT   = 22
FAR_3_NODE_RIGHT  = 23
NEAR_2_NODE       = 24

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

    def get_node_type(self):
        if self.parent == None:
            return ROOT

        if self == self.parent.children[0]:
            return LEFT

        if self.parent.is_three_node():
            if self == self.parent.children[1]:
                return CENTER
            elif self == self.parent.children[2]:
                return RIGHT
        else:
            if self == self.parent.children[1]:
                return RIGHT

    def get_right_sibling(self):
        if self.parent.is_three_node():
            node_type = self.get_node_type()
            if node_type == LEFT:
                return self.parent.children[1]
            elif node_type == CENTER:
                return self.parent.children[2]
            return None
        return self.parent.children[1]

    def get_left_sibling(self):
        if self.parent.is_three_node():
            node_type = self.get_node_type()
            if node_type == RIGHT:
                return self.parent.children[1]
            elif node_type == CENTER:
                return self.parent.children[0]
            return None
        return self.parent.children[0]

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
        for i in xrange(len(self.parent.children)):
            if self.parent.children[i] == self:
                return self.parent.keys[i - 1]

        return None

    def get_right_parent_key(self):
        for i in xrange(len(self.parent.children)):
            if self.parent.children[i] == self:
                return self.parent.keys[i]

        return None

    def set_left_parent_key(self, key):
        for i in xrange(len(self.parent.children)):
            if self.parent.children[i] == self:
                if key is None:
                    self.parent.keys.pop(i - 1)
                    self.parent.children.pop(i - 1)
                else:
                    self.parent.keys[i - 1] = key

                break;

    def set_right_parent_key(self, key):
        for i in xrange(len(self.parent.children)):
            if self.parent.children[i] == self:
                if key is None:
                    self.parent.keys.pop(i)
                    self.parent.children.pop(i + 1)
                else:
                    self.parent.keys[i] = key

                break;

    def remove_leaf_3_node_key(self, key):
        assert self.is_leaf()
        assert self.is_three_node()
        assert key in self.keys

        if key == self.keys[0]:
            self.keys[0] = self.keys[1]
            del self.keys[1]

        elif key == self.keys[1]:
            del self.keys[1]




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
        if key in node.keys:
            return (True, node)

        child_node = node.get_child_for_key(key)
        if child_node is not None:
            return self.search(child_node, key)

        return (False, node)

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

    def _get_node_sibling_type(self, node):
        if (node.parent.is_three_node()):
            if node == node.parent.children[0]:
                # LEFT
                if node.parent.children[1].is_three_node():
                    return NEAR_3_NODE_RIGHT
                elif node.parent.children[2].is_three_node():
                    return FAR_3_NODE_RIGHT
            elif node == node.parent.children[1]:
                # CENTER
                if node.parent.children[0].is_three_node():
                    return NEAR_3_NODE_LEFT
                elif node.parent.children[2].is_three_node():
                    return NEAR_3_NODE_RIGHT
            if node == node.parent.children[2]:
                # LEFT
                if node.parent.children[0].is_three_node():
                    return FAR_3_NODE_LEFT
                elif node.parent.children[1].is_three_node():
                    return NEAR_3_NODE_LEFT
        else:
            if node == node.parent.children[0]:
                # LEFT
                if node.parent.children[1].is_three_node():
                    return NEAR_3_NODE_RIGHT
            elif node == node.parent.children[1]:
                # RIGHT
                if node.parent.children[0].is_three_node():
                    return NEAR_3_NODE_LEFT

        return NEAR_2_NODE

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
        logging.debug('node.children: (%s)', '; '.join(map(str, node.children)))
        logging.debug('parent.children: (%s)', '; '.join(map(str, node.parent.children)))

        node.insert_key(node.get_left_parent_key())
        node.set_left_parent_key(sibling.pop_last_key())
        node.insert_child(sibling.pop_last_child())

        logging.debug('_rotate_right complete, node: (%s), parent: (%s), sibling: (%s)', \
            node, node.parent, sibling)
        logging.debug('node.children: (%s)', '; '.join(map(str, node.children)))
        logging.debug('parent.children: (%s)', '; '.join(map(str, node.parent.children)))

    def _double_rotate_left(self, node):
        sibling = node.get_right_sibling()
        logging.debug('_double_rotate_left, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        self._rotate_left(node)
        self._rotate_left(sibling)

    def _double_rotate_right(self, node):
        sibling = node.get_left_sibling()
        logging.debug('_double_rotate_right, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        self._rotate_right(node)
        self._rotate_right(sibling)

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

        sibling_type = self._get_node_sibling_type(node)

        if sibling_type == NEAR_3_NODE_LEFT:
            self._rotate_right(node)
        elif sibling_type == NEAR_3_NODE_RIGHT:
            self._rotate_left(node)
        elif sibling_type == FAR_3_NODE_LEFT:
            self._double_rotate_right(node)
        elif sibling_type == FAR_3_NODE_RIGHT:
            self._double_rotate_left(node)
        elif sibling_type == NEAR_2_NODE:
            node_type = node.get_node_type()
            if node.parent.is_two_node():
                if node_type == LEFT:
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
                if node_type == LEFT:
                    self._rotate_left(node)
                    self._rotate_right(node.get_right_sibling().get_right_sibling())
                elif node_type == CENTER:
                    self._rotate_right(node.get_right_sibling())
                else:
                    self._rotate_right(node)
                    self._rotate_left(node.get_left_sibling().get_left_sibling())

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
