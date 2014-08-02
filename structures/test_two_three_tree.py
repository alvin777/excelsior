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


    # def insert_key(self, key):
    #     # 2-node
    #     #   - lt key
    #     #   - gt key
    #     # 3-node
    #     #   - lt key 1
    #     #   - lt key 2
    #     #   - gt key 2
    #     if len(self.keys) < 1 or len(self.keys) > 2:
    #         raise Exception()

    # def get_child_for_key(self, key):
    #     for i in xrange(len(self.keys)):
    #         if key < keys[i]:
    #             return self.children[i]

    #     return children[-1]


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

        child_node = self.get_child_for_key(node, key)
        if child_node is not None:
            return self.search(child_node, key)

        return (False, node)

    def get_node_height(self, node):
        height = 0
        while node:
            height += 1
            node = node.parent

        return height

    def get_child_for_key(self, node, key):
        if len(node.children) == 0:
            return None

        for i in xrange(len(node.keys)):
            if key < node.keys[i]:
                return node.children[i]

        return node.children[-1]

    def insert(self, key):
        if self.root is None:
            self.root = TwoThreeNode(None, key)

        (found, target_node) = self.search(self.root, key)

        if found:
            return   # do not allow same values

        self.insert_key_new_pos(target_node, key)

    def insert_key_new_pos(self, node, key):
        # assert node has no children
        # assert no duplicate keys

        if key > node.keys[-1]:
            node.keys.append(key)
        else:
            insert_pos = 0
            while insert_pos < len(node.keys) and key > node.keys[insert_pos]:
                insert_pos += 1

            node.keys.insert(insert_pos, key)

        if len(node.keys) >= 3:
            self.fix_tree(node)

    def fix_tree(self, node):
        # assert node has three keys

        (key, left, right) = self.split_node(node)

        # print 'fix_tree node: {}, key: {}, left: {}, right: {}'.format(node, key, left, right)

        if node.parent:
            self.merge_node(node.parent, key, left, right)
            if len(node.parent.keys) >= 3:
                self.fix_tree(node.parent)
        else:
            # root
            self.root = TwoThreeNode(None, key, left, right)

    def split_node(self, node):
        # assert node has three keys
        # assert node has four children

        children = [None]*4 if len(node.children) == 0 else node.children

        left = TwoThreeNode(node, node.keys[0], children[0], children[1])
        key = node.keys[1]
        right = TwoThreeNode(node, node.keys[2], children[2], children[3])
        return (key, left, right)

    def merge_node(self, node, key, left, right):

        # print 'merge_node node: {}, key: {}, left: {}, right: {}'.format(node, key, left, right)
        if key > node.keys[-1]:
            node.keys.append(key)
            node.children[-1] = left
            node.children.append(right)
        else:
            insert_pos = 0
            while insert_pos < len(node.keys) and key > node.keys[insert_pos]:
                insert_pos += 1

            node.keys.insert(insert_pos, key)
            node.children[insert_pos] = left
            node.children.insert(insert_pos+1, right)
            
        left.parent = node
        right.parent = node


    def is_leaf(self, node):
        return len(node.children) == 0

    def is_three_node(self, node):
        return len(node.keys) == 2

    def is_two_node(self, node):
        return len(node.keys) == 1

    def get_node_type(self, node):
        if node.parent == None:
            return ROOT

        if node == node.parent.children[0]:
            return LEFT

        if self.is_three_node(node.parent):
            if node == node.parent.children[1]:
                return CENTER
            elif node == node.parent.children[2]:
                return RIGHT
        else:
            if node == node.parent.children[1]:
                return RIGHT

    def get_node_sibling_type(self, node):
        if (self.is_three_node(node.parent)):
            if node == node.parent.children[0]:
                # LEFT
                if self.is_three_node(node.parent.children[1]):
                    return NEAR_3_NODE_RIGHT
                elif self.is_three_node(node.parent.children[2]):
                    return FAR_3_NODE_RIGHT
            elif node == node.parent.children[1]:
                # CENTER
                if self.is_three_node(node.parent.children[0]):
                    return NEAR_3_NODE_LEFT
                elif self.is_three_node(node.parent.children[2]):
                    return NEAR_3_NODE_RIGHT
            if node == node.parent.children[2]:
                # LEFT
                if self.is_three_node(node.parent.children[0]):
                    return FAR_3_NODE_LEFT
                elif self.is_three_node(node.parent.children[1]):
                    return NEAR_3_NODE_LEFT
        else:
            if node == node.parent.children[0]:
                # LEFT
                if self.is_three_node(node.parent.children[1]):
                    return NEAR_3_NODE_RIGHT
            elif node == node.parent.children[1]:
                # RIGHT
                if self.is_three_node(node.parent.children[0]):
                    return NEAR_3_NODE_LEFT

        return NEAR_2_NODE

    def get_right_sibling(self, node):
        if self.is_three_node(node.parent):
            node_type = self.get_node_type(node)
            if node_type == LEFT:
                return node.parent.children[1]
            elif node_type == CENTER:
                return node.parent.children[2]
            return None
        return node.parent.children[1]

    def get_left_sibling(self, node):
        if self.is_three_node(node.parent):
            node_type = self.get_node_type(node)
            if node_type == RIGHT:
                return node.parent.children[1]
            elif node_type == CENTER:
                return node.parent.children[0]
            return None
        return node.parent.children[0]

    def pop_last_key(self, node):
        if len(node.keys) == 0:
            return None

        return node.keys.pop()

    def pop_first_key(self, node):
        if len(node.keys) == 0:
            return None

        key = node.keys[0]
        node.keys = node.keys[1:]
        return key

    def pop_last_child(self, node):
        if len(node.children) == 0:
            return None

        return node.children.pop()

    def pop_first_child(self, node):
        if len(node.children) == 0:
            return None

        child = node.children[0]
        node.children = node.children[1:]
        return child

    def insert_key(self, node, key):
        node.keys.insert(0, key)

    def append_key(self, node, key):
        node.keys.append(key)

    def insert_child(self, node, child):
        if child is None:
            return

        node.children.insert(0, child)
        child.parent = node

    def append_child(self, node, child):
        if child is None:
            return

        node.children.append(child)
        child.parent = node

    def get_left_parent_key(self, node):
        for i in xrange(len(node.parent.children)):
            if node.parent.children[i] == node:
                return node.parent.keys[i - 1]

        return None

    def get_right_parent_key(self, node):
        for i in xrange(len(node.parent.children)):
            if node.parent.children[i] == node:
                return node.parent.keys[i]

        return None

    def set_left_parent_key(self, node, key):
        for i in xrange(len(node.parent.children)):
            if node.parent.children[i] == node:
                if key is None:
                    node.parent.keys.pop(i - 1)
                    node.parent.children.pop(i - 1)
                else:
                    node.parent.keys[i - 1] = key

                break;

    def set_right_parent_key(self, node, key):
        for i in xrange(len(node.parent.children)):
            if node.parent.children[i] == node:
                if key is None:
                    node.parent.keys.pop(i)
                    node.parent.children.pop(i + 1)
                else:
                    node.parent.keys[i] = key

                break;

    def rotate_left(self, node):
        sibling = self.get_right_sibling(node)

        logging.debug('rotate_left, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        self.append_key(node, self.get_right_parent_key(node))
        self.set_right_parent_key(node, self.pop_first_key(sibling))
        self.append_child(node, self.pop_first_child(sibling))

        logging.debug('rotate_left complete, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

    def rotate_right(self, node):
        sibling = self.get_left_sibling(node)

        logging.debug('rotate_right, node: (%s), parent: (%s), sibling: (%s)', \
            node, node.parent, sibling)
        logging.debug('node.children: (%s)', '; '.join(map(str, node.children)))
        logging.debug('parent.children: (%s)', '; '.join(map(str, node.parent.children)))

        self.insert_key(node, self.get_left_parent_key(node))
        self.set_left_parent_key(node, self.pop_last_key(sibling))
        self.insert_child(node, self.pop_last_child(sibling))

        logging.debug('rotate_right complete, node: (%s), parent: (%s), sibling: (%s)', \
            node, node.parent, sibling)
        logging.debug('node.children: (%s)', '; '.join(map(str, node.children)))
        logging.debug('parent.children: (%s)', '; '.join(map(str, node.parent.children)))

    def double_rotate_left(self, node):
        sibling = self.get_right_sibling(node)
        logging.debug('double_rotate_left, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        self.rotate_left(node)
        self.rotate_left(sibling)

    def double_rotate_right(self, node):
        sibling = self.get_left_sibling(node)
        logging.debug('double_rotate_right, node: (%s), parent: (%s), sibling: (%s)', node, node.parent, sibling)

        self.rotate_right(node)
        self.rotate_right(sibling)

    def remove_leaf_3_node_key(self, node, key):
        assert self.is_leaf(node)
        assert self.is_three_node(node)
        assert key in node.keys

        if key == node.keys[0]:
            node.keys[0] = node.keys[1]
            del node.keys[1]

        elif key == node.keys[1]:
            del node.keys[1]

    def find_predessor(self, node, key):
        assert not self.is_leaf(node)

        for i in xrange(len(node.keys)):
            if node.keys[i] == key:
                left_child = node.children[i]
                break

        if self.is_leaf(left_child):
            return left_child

        rightmost_child = left_child.children[-1]
        while not self.is_leaf(rightmost_child):
            rightmost_child = rightmost_child.children[-1]

        return rightmost_child

    def swap_keys(self, node, predessor, key):
        logging.debug('swap_keys, node: (%s), predessor: (%s), key: (%s)', node, predessor, key)
        for i in xrange(len(node.keys)):
            if node.keys[i] == key:

                node.keys[i], predessor.keys[-1] = predessor.keys[-1], node.keys[i]
                break
        logging.debug('swap_keys complete, node: (%s), predessor: (%s), key: (%s)', node, predessor, key)

    def remove(self, key):
        # find node
        # if not leaf - swap
        # fix empty node
        logging.debug('remove, key: %d', key)
        
        (found, node) = self.search(self.root, key)

        logging.debug('node to remove: (%s)', node)

        if not found:
            return

        if not self.is_leaf(node):
            predessor = self.find_predessor(node, key)
            logging.debug('predessor: (%s)', predessor)
            self.swap_keys(node, predessor, key)
            logging.debug('after swap, node: (%s), predessor: (%s)', node, predessor)
            node = predessor

        if self.is_three_node(node):
            self.remove_leaf_3_node_key(node, key)
            return

        self.pop_last_key(node)
        self.pop_last_child(node)

        self.remove_node(node)

    def remove_node(self, node):

        if node == self.root and self.is_leaf(self.root):
            self.root = None
            return

        sibling_type = self.get_node_sibling_type(node)

        if sibling_type == NEAR_3_NODE_LEFT:
            self.rotate_right(node)
        elif sibling_type == NEAR_3_NODE_RIGHT:
            self.rotate_left(node)
        elif sibling_type == FAR_3_NODE_LEFT:
            self.double_rotate_right(node)
        elif sibling_type == FAR_3_NODE_RIGHT:
            self.double_rotate_left(node)
        elif sibling_type == NEAR_2_NODE:
            node_type = self.get_node_type(node)
            if self.is_two_node(node.parent):
                if node_type == LEFT:
                    self.rotate_left(node)
                    self.rotate_left(node)
                else:
                    self.rotate_right(node)
                    self.rotate_right(node)

                if node.parent == self.root:
                    self.root = node
                    node.parent = None
                else:
                    self.remove_node(node.parent)

            else:
                if node_type == LEFT:
                    self.rotate_left(node)
                    self.rotate_right(self.get_right_sibling(self.get_right_sibling(node)))
                elif node_type == CENTER:
                    self.rotate_right(self.get_right_sibling(node))
                else:
                    self.rotate_right(node)
                    self.rotate_left(self.get_left_sibling(self.get_left_sibling(node)))

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

        if tree.is_leaf(node):
            if self.tree_height is None:
                self.tree_height = tree.get_node_height(node)
            else:
                self.assertEquals(self.tree_height, tree.get_node_height(node))
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
        # random.seed()
        # random_list = [random.randint(0, 2**30) for _ in xrange(len(1000))]
        # sorted_list = [x for x in xrange(10000)]
        # shuffled_list = sorted_list
        # random.shuffle(shuffled_list)

        tree = TwoThreeTree()
        reference_list = []

        for i in xrange(10000):
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

        def make_list(node):
            tree_list.extend(node.keys)

        tree.breadth_first_search(make_list)

        self.assertEquals(sorted(reference_list), sorted(tree_list))


# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.DEBUG)
# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.INFO)
