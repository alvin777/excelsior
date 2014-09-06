import unittest
import logging
import random


class Color:
    RED = 1
    BLACK = 2


def print_tree(tree):
    for node in tree.parent_children_iterator():
        side = ""
        if node.parent:
            if node == node.parent.right:
                side = "r: "
            elif node == node.parent.left:
                side = "l: "
            else:
                side = "?: "
        logging.debug("    " * node.get_height() + side + str(node))


class LLRBTreeNode:
    def __init__(self, parent, key, color):
        self.parent = parent
        self.key = key
        self.color = color
        self.right = None
        self.left = None

    def __str__(self):
        return "({}, {})".format(self.key, "RED" if self.color == Color.RED else "BLACK")

    def is_leaf(self):
        return self.left is None and self.right is None

    def rotate_left(self):
        logging.debug("rotating node %s to the left", self)

        assert self.right is not None

        # remember variables
        parent = self.parent
        right = self.right
        right_left = self.right.left

        # reparent right.left
        if right.left is not None:
            right.left.parent = self

        # make right node parent
        right.parent = parent
        right.left = self
        right.color = self.color

        # make self child of former right node
        self.parent = right
        self.right = right_left
        self.color = Color.RED

        if parent is not None:
            # fix parent link
            if parent.left == self:
                parent.left = right
            else:
                assert parent.right == self
                parent.right = right

        return self.parent

    def rotate_right(self):
        logging.debug("rotating node %s to the right", self)

        assert self.left is not None

        # remember variables
        parent = self.parent
        left = self.left
        left_right = self.left.right

        # reparent right.left
        if left.right is not None:
            left.right.parent = self

        # make right node parent
        left.parent = parent
        left.right = self
        left.color = self.color

        # make self child of former right node
        self.parent = left
        self.left = left_right
        self.color = Color.RED

        if parent is not None:
            # fix parent link
            if parent.right == self:
                parent.right = left
            else:
                assert parent.left == self
                parent.left = left

        return self.parent

    def flip_colors(self):
        logging.debug("flipping %s", self)

        assert not self.is_leaf()

        def flip(color):
            return Color.RED if color == Color.BLACK else Color.BLACK

        self.color = flip(self.color)
        self.left.color = flip(self.left.color)
        self.right.color = flip(self.right.color)

    def has_red_sibling(self):
        if self.parent is None:
            return

        if self == self.parent.left:
            if self.parent.right is not None:
                return self.parent.right.color == Color.RED
        else:
            if self.parent.left is not None:
                return self.parent.left.color == Color.RED

        return False

    def get_height(self):
        height = 0
        node = self

        while node.parent is not None:
            node = node.parent
            height += 1
        return height


class LLRBTree:
    def __init__(self):
        self.root = None

    def _is_red(self, node):
        return node is not None and node.color == Color.RED

    def _find_node(self, key):
        assert self.root is not None

        node = self.root
        parent = None

        while node is not None:
            parent = node

            if key == node.key:
                return node

            node = node.right if key > node.key else node.left

        return parent

    def _fix_up(self, node):
        logging.debug("fixing up from node: %s", node)

        while node is not None:
            if not self._is_red(node.left) and self._is_red(node.right):
                node = node.rotate_left()

            if self._is_red(node.left) and self._is_red(node.left.left):
                node = node.rotate_right()

            if self._is_red(node.left) and self._is_red(node.right):
                node.flip_colors()

            self.root = node

            node = node.parent

        if self.root is not None:
            self.root.color = Color.BLACK

    def insert(self, key):
        logging.debug("")
        logging.debug("inserting %s", key)

        if self.root is None:
            self.root = LLRBTreeNode(None, key, Color.BLACK)
            return

        parent = self._find_node(key)
        node = LLRBTreeNode(parent, key, Color.RED)

        logging.debug("node to insert to: %s", parent)
        logging.debug("root before: %s", self.root)

        if key > parent.key:
            assert parent.right is None
            parent.right = node
        else:
            assert parent.left is None
            parent.left = node

        self._fix_up(node.parent)

        logging.debug("root after: %s", self.root)

    def _move_red_to_left(self, node):
        logging.debug("moving red from %s to the left", node)

        if node.is_leaf(): 
            return

        node.flip_colors()
        if self._is_red(node.right.left):
            node.right.rotate_right()
            node = node.rotate_left()
            node.flip_colors()

    def _move_red_to_right(self, node):
        logging.debug("moving red from %s to the right", node)

        if node.is_leaf(): 
            return node

        print_tree(self)
        node.flip_colors()
        print_tree(self)

        if self._is_red(node.left.left):
            node.rotate_right()
            print_tree(self)
            node.rotate_left()
            print_tree(self)
            node.parent.parent.flip_colors()
            print_tree(self)

            return node.parent

        return node.right

    def _find_min(self, node):
        while node.left is not None:
            node = node.left
        return node

    def _delete_node(self, node):
        logging.debug("_delete_node %s", node)

        if node == self.root:
            self.root = None
            return

        assert node.color == Color.RED

        if node == node.parent.left:
            node.parent.left = None
        else:
            node.parent.right = None

        node.parent = None

    def delete(self, key):
        # push down red color to key node
        # if not leaf - swap with min
        # push down red color to min node
        # delete red min node
        # fix up

        logging.debug("")
        logging.debug("deleting %s", key)

        node = self.root
        parent_node = node.parent

        if self.root is None:
            return

        logging.debug("before push down:")
        # print_tree(self)

        while node is not None:
            logging.debug("processing %s", node)

            node_key = node.key

            if node.key == key:
                logging.debug("found node to delete: %s", node)
                logging.debug("node is %s", "leaf" if node.is_leaf() else "not leaf")

                if node.is_leaf():
                    print_tree(self)

                    parent_node = node.parent
                    self._delete_node(node)

                    print_tree(self)
                    break
                elif node.right is None:
                    print_tree(self)

                    node.rotate_right()
                    parent_node = node.parent
                    self._delete_node(node)

                    print_tree(self)
                else:
                    min_node = self._find_min(node.right)  # TODO: optimize
                    logging.debug("looking for min node: %s", min_node)
                    node.key = min_node.key
                    key = node.key

            logging.debug("comparing key %s to node key %s", key, node.key)

            parent_node = node

            if key < node_key:
                # push red color to left
                if node.left is not None and not self._is_red(node.left) and not self._is_red(node.left.left):
                    self._move_red_to_left(node)
                node = node.left
            else:
                # push red color to right
                if self._is_red(node.left):
                    node.rotate_right()

                # if node.right is not None and \
                #    not self._is_red(node.right) and \
                #    node.right.left is not None and \
                #    not self._is_red(node.right.left):
                if not self._is_red(node.right) and \
                   not self._is_red(node.right.left):
                    node = self._move_red_to_right(node)
                else:
                    node = node.right


        logging.debug("after push down:")
        # print_tree(self)

        self._fix_up(parent_node)

    def parent_children_iterator(self):

        queue = []
        if self.root is not None:
            queue.append(self.root)

        while len(queue) > 0:
            node = queue.pop(0)
            yield node
            if node.right is not None:
                queue.insert(0, node.right)
            if node.left is not None:
                queue.insert(0, node.left)


class TestLLRBTree(unittest.TestCase):
    def assertNode(self, node, key, color, left_exists, right_exists):
        self.assertEquals(node.key, key)
        self.assertEquals(node.color, color)
        self.assertEquals(node.left is not None, left_exists)
        self.assertEquals(node.right is not None, right_exists)

        if node.left is not None:
            self.assertEquals(node.left.parent, node)

        if node.right is not None:
            self.assertEquals(node.right.parent, node)

    def create_tree(self, data):
        tree = LLRBTree()
        for element in data:
            tree.insert(element)
        return tree

    def get_black_height(self, node):
        height = 0

        while node.parent is not None:
            if node.color == Color.BLACK:
                height += 1
            node = node.parent

        return height

    def is_valid(self, tree):
        self.assertFalse(tree.root and tree.root.color == Color.RED)

        black_height = None
        for node in tree.parent_children_iterator():
            self.assertFalse(node.right is not None and node.right.color == Color.RED)

            if node.color == Color.RED:
                self.assertFalse(node.left is not None and node.left.color == Color.RED)

            self.assertFalse(node.right is not None and node.right.key < node.key)
            self.assertFalse(node.left is not None and node.left.key > node.key)

            if node.left is not None or node.right is not None:
                continue

            if black_height is None:
                black_height = self.get_black_height(node)
            else:
                self.assertTrue(self.get_black_height(node) == black_height)

        return True

    def test_empty(self):
        tree = LLRBTree()
        self.assertEquals(tree.root, None)

    def test_1(self):
        tree = LLRBTree()
        tree.insert(1)
        self.assertEquals(tree.root.key, 1)
        self.assertEquals(tree.root.color, Color.BLACK)
        self.assertEquals(tree.root.parent, None)
        self.assertEquals(tree.root.left, None)
        self.assertEquals(tree.root.right, None)

    def test_12(self):
        tree = self.create_tree([1, 2])
        self.assertNode(tree.root, 2, Color.BLACK, True, False)
        self.assertNode(tree.root.left, 1, Color.RED, False, False)

    def test_21(self):
        tree = self.create_tree([2, 1])
        self.assertNode(tree.root, 2, Color.BLACK, True, False)
        self.assertNode(tree.root.left, 1, Color.RED, False, False)

    def test_135(self):
        tree = self.create_tree([1, 3, 5])
        self.assertNode(tree.root, 3, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 1, Color.BLACK, False, False)
        self.assertNode(tree.root.right, 5, Color.BLACK, False, False)

    def test_130(self):
        tree = self.create_tree([1, 3, 0])
        self.assertNode(tree.root, 1, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 0, Color.BLACK, False, False)
        self.assertNode(tree.root.right, 3, Color.BLACK, False, False)

    def test_132(self):
        tree = self.create_tree([1, 3, 2])
        self.assertNode(tree.root, 2, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 1, Color.BLACK, False, False)
        self.assertNode(tree.root.right, 3, Color.BLACK, False, False)

    # def test_parent_children_iterator(self):
    #     tree = self.create_tree([1, 2, 3])

    #     for number in xrange(4, 8):
    #         tree.insert(number)
    #         print
    #         for node in tree.parent_children_iterator():
    #             print "    " * node.get_height() + str(node)

    def test_7(self):
        tree = self.create_tree(xrange(1, 8))
        print_tree(tree)
        self.assertNode(tree.root, 4, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 2, Color.BLACK, True, True)
        self.assertNode(tree.root.right, 6, Color.BLACK, True, True)
        self.assertNode(tree.root.left.left,  1, Color.BLACK, False, False)
        self.assertNode(tree.root.left.right, 3, Color.BLACK, False, False)
        self.assertNode(tree.root.right.left,  5, Color.BLACK, False, False)
        self.assertNode(tree.root.right.right, 7, Color.BLACK, False, False)

    # def test_assert_valid_rb_tree(self):
    #     tree = self.create_tree(xrange(1, 8))
    #     self.assertTrue(self.is_valid(tree))

    #     # assert root is black
    #     tree = self.create_tree(xrange(1, 8))
    #     tree.root.color = Color.RED
    #     self.assertFalse(self.is_valid(tree))

    #     # assert equal black height
    #     tree = self.create_tree(xrange(1, 8))
    #     tree.root.left.color = Color.RED
    #     self.assertFalse(self.is_valid(tree))

    #     # assert rb-tree is left-leaning
    #     tree = self.create_tree(xrange(1, 8))
    #     tree.root.left.color = Color.RED
    #     tree.root.right.color = Color.RED
    #     self.assertFalse(self.is_valid(tree))

    #     # assert sequental red nodes
    #     tree = LLRBTree()
    #     tree.root = LLRBTreeNode(None, 5, Color.BLACK)
    #     tree.root.left = LLRBTreeNode(tree.root, 3, Color.RED)
    #     tree.root.left.left = LLRBTreeNode(tree.root.left, 1, Color.RED)
    #     self.assertFalse(self.is_valid(tree))

    def test_random_insert(self):
        tree = LLRBTree()
        for number in [random.randint(0, 2**30) for _ in xrange(1000)]:
            tree.insert(number)
        self.assertTrue(self.is_valid(tree))
        # print_tree(tree)

    #
    # deletion
    #

    def test_delete_root(self):
        tree = LLRBTree()
        tree.insert(1)

        tree.delete(1)
        self.assertEquals(tree.root, None)

    def test_delete_non_existing(self):
        tree = self.create_tree([1, 2, 3])

        print_tree(tree)
        tree.delete(5)
        tree.delete(0)
        print_tree(tree)

        self.assertNode(tree.root, 2, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 1, Color.BLACK, False, False)
        self.assertNode(tree.root.right, 3, Color.BLACK, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_1(self):
        tree = self.create_tree([1, 2, 3])           #   2
        tree.delete(1)                               # 1   3

        self.assertNode(tree.root, 3, Color.BLACK, True, False)
        self.assertNode(tree.root.left, 2, Color.RED, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_3(self):
        tree = self.create_tree([1, 2, 3])
        tree.delete(3)

        self.assertNode(tree.root, 2, Color.BLACK, True, False)
        self.assertNode(tree.root.left, 1, Color.RED, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_2(self):
        tree = self.create_tree([1, 2, 3])
        tree.delete(2)

        self.assertNode(tree.root, 3, Color.BLACK, True, False)
        self.assertNode(tree.root.left, 1, Color.RED, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_7_7(self):
        tree = self.create_tree(xrange(1, 8))
        tree.delete(7)

        self.assertNode(tree.root,            4, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       2, Color.RED,   True, True)
        self.assertNode(tree.root.right,      6, Color.BLACK, True, False)
        self.assertNode(tree.root.left.left,  1, Color.BLACK, False, False)
        self.assertNode(tree.root.left.right, 3, Color.BLACK, False, False)
        self.assertNode(tree.root.right.left, 5, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_node_parent_left(self):
        tree = self.create_tree([1, 2, 3, 4, 5])  #   2,4     =>    4
        tree.delete(1)                            # 1  3  5      2,3  5

        self.assertNode(tree.root,            4, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       3, Color.BLACK, True, False)
        self.assertNode(tree.root.right,      5, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left,  2, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_node_parent_middle(self):
        tree = self.create_tree([1, 2, 3, 4, 5])  #   2,4     =>     4
        tree.delete(3)                            # 1  3  5      1,2   5

        self.assertNode(tree.root,            4, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       2, Color.BLACK, True, False)
        self.assertNode(tree.root.right,      5, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left,  1, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_3_node_parent_right(self):
        tree = self.create_tree([1, 2, 3, 4, 5])  #   2,4     =>   2
        tree.delete(5)                            # 1  3  5      1   3,4

        print_tree(tree)

        self.assertNode(tree.root,            2, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       1, Color.BLACK, False, False)
        self.assertNode(tree.root.right,      4, Color.BLACK, True, False)
        self.assertNode(tree.root.right.left,  3, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_4_node_parent_left(self):
        tree = self.create_tree(xrange(1, 8))     #     4 
        tree.delete(1)                            #   2    6    =>   2,4,6    =>      4,6     =>     4,6
                                                  #  1 3  5 7      1  3 5  7      1,2,3  5 7     2,3  5  7

        self.assertNode(tree.root,            6, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       4, Color.RED,   True, True)
        self.assertNode(tree.root.right,      7, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left,  3, Color.BLACK, True, False)
        self.assertNode(tree.root.left.right, 5, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left.left,2, Color.RED, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_4_node_parent_middle1(self):
        tree = self.create_tree(xrange(1, 8))     #     4
        tree.delete(3)                            #   2    6    =>     4,6
                                                  #  1 3  5 7      1,2  5  7

        self.assertNode(tree.root,            6, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       4, Color.RED,   True, True)
        self.assertNode(tree.root.right,      7, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left,  2, Color.BLACK, True, False)
        self.assertNode(tree.root.left.right, 5, Color.BLACK, False, False)
        self.assertNode(tree.root.left.left.left,1, Color.RED, False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_4_node_parent_middle2(self):
        tree = self.create_tree(xrange(1, 8))     #     4
        tree.delete(5)                            #   2    6    =>   2,4
                                                  #  1 3  5 7      1 3  6,7

        self.assertNode(tree.root,            4, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       2, Color.RED,   True, True)
        self.assertNode(tree.root.right,      7, Color.BLACK, True, False)
        self.assertNode(tree.root.left.left,  1, Color.BLACK, False, False)
        self.assertNode(tree.root.left.right, 3, Color.BLACK, False, False)
        self.assertNode(tree.root.right.left, 6, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_delete_4_node_parent_right(self):
        tree = self.create_tree(xrange(1, 8))     #     4
        tree.delete(7)                            #   2    6    =>    2,4
                                                  #  1 3  5 7       1 3  5,6

        self.assertNode(tree.root,            4, Color.BLACK, True, True)
        self.assertNode(tree.root.left,       2, Color.RED,   True, True)
        self.assertNode(tree.root.right,      6, Color.BLACK, True, False)
        self.assertNode(tree.root.left.left,  1, Color.BLACK, False, False)
        self.assertNode(tree.root.left.right, 3, Color.BLACK, False, False)
        self.assertNode(tree.root.right.left, 5, Color.RED,   False, False)

        self.assertTrue(self.is_valid(tree))

    def test_random_data(self):
        tree = LLRBTree()
        reference_list = []

        for i in xrange(1000):
            print_tree(tree)

            if (len(reference_list) == 0) or (random.random() >= 0.25):
                # new_value = random.randint(0, 2**30)
                new_value = random.randint(0, 1000)
                logging.debug("inserting value: %d", new_value)

                tree.insert(new_value)
                reference_list.append(new_value)
            else:
                value_index_to_delete = random.randint(0, len(reference_list) - 1)
                value_to_delete = reference_list[value_index_to_delete]
                logging.debug("deleting value: %d", value_to_delete)

                print_tree(tree)
                tree.delete(value_to_delete)
                reference_list.pop(value_index_to_delete)

            print_tree(tree)

            is_valid = self.is_valid(tree)


    def test_delete_issue_1(self):
        tree = self.create_tree([72, 42, 82, 15, 43, 75, 11])
        print_tree(tree)
        tree.delete(43)
        print_tree(tree)

        self.assertTrue(self.is_valid(tree))

    def test_delete_issue_2(self):
        tree = self.create_tree([1, 2])
        print_tree(tree)
        tree.delete(1)
        print_tree(tree)

        self.assertTrue(self.is_valid(tree))

# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.DEBUG)
