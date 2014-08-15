import unittest
import logging
import random


class Color:
    RED = 1
    BLACK = 2


class RBTreeNode:
    def __init__(self, parent, key, color):
        self.parent = parent
        self.key = key
        self.color = color
        self.right = None
        self.left = None

    def __str__(self):
        return "({}, {})".format(self.key, "RED" if self.color == Color.RED else "BLACK")

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

    def flip_colors(self):
        assert self.left is not None
        assert self.right is not None

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


class RBTree:
    def __init__(self):
        self.root = None

    def insert(self, key):
        logging.debug("")
        logging.debug("inserting %s", key)

        if self.root is None:
            self.root = RBTreeNode(None, key, Color.BLACK)
            return

        parent = self._find_node(key)
        node = RBTreeNode(parent, key, Color.RED)

        logging.debug("node to insert to: %s", parent)
        logging.debug("root before: %s", self.root)

        if key > parent.key:
            assert parent.right is None
            parent.right = node
        else:
            assert parent.left is None
            parent.left = node

        self._fix_insert(node)

        #fix root
        while self.root.parent is not None:
            self.root = self.root.parent

        self.root.color = Color.BLACK

        logging.debug("root after: %s", self.root)

    def _find_node(self, key):
        assert self.root is not None

        node = self.root
        parent = None

        while node is not None:
            parent = node
            node = node.right if key > node.key else node.left

        return parent

    def _fix_insert(self, node):
        if node is None or node.parent is None:
            return

        if node.color == Color.BLACK:
            return

        if node.parent.color == Color.BLACK:
            if node.has_red_sibling():
                node.parent.flip_colors()
                self._fix_insert(node.parent)
            elif node == node.parent.right:
                node.parent.rotate_left()
        else:
            middle = node.parent
            if node == node.parent.right:
                node.parent.rotate_left()
                middle = node
            middle.parent.rotate_right()
            middle.flip_colors()
            self._fix_insert(middle)

    def parent_children_iterator(self):
        queue = [self.root]

        while len(queue) > 0:
            node = queue.pop(0)
            yield node
            if node.right is not None:
                queue.insert(0, node.right)
            if node.left is not None:
                queue.insert(0, node.left)


class TestRBTree(unittest.TestCase):
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
        tree = RBTree()
        for element in data:
            tree.insert(element)
        return tree

    def print_tree(self, tree):
        for node in tree.parent_children_iterator():
            print "    " * node.get_height() + str(node)

    def get_black_height(self, node):
        height = 0

        while node.parent is not None:
            if node.color == Color.BLACK:
                height += 1
            node = node.parent

        return height

    def is_rb_tree_valid(self, tree):
        if tree.root and tree.root.color == Color.RED:
            return False

        black_height = None
        for node in tree.parent_children_iterator():
            if node.right is not None and node.right.color == Color.RED:
                return False

            if node.color == Color.RED:
                if node.left is not None and node.left.color == Color.RED:
                    return False

            if node.left is not None or node.right is not None:
                continue

            if black_height is None:
                black_height = self.get_black_height(node)
            else:
                if self.get_black_height(node) != black_height:
                    return False

        return True

    def test_empty(self):
        tree = RBTree()
        self.assertEquals(tree.root, None)

    def test_1(self):
        tree = RBTree()
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
        # self.print_tree(tree)
        self.assertNode(tree.root, 4, Color.BLACK, True, True)
        self.assertNode(tree.root.left, 2, Color.BLACK, True, True)
        self.assertNode(tree.root.right, 6, Color.BLACK, True, True)
        self.assertNode(tree.root.left.left,  1, Color.BLACK, False, False)
        self.assertNode(tree.root.left.right, 3, Color.BLACK, False, False)
        self.assertNode(tree.root.right.left,  5, Color.BLACK, False, False)
        self.assertNode(tree.root.right.right, 7, Color.BLACK, False, False)

    def test_assert_valid_rb_tree(self):
        tree = self.create_tree(xrange(1, 8))
        self.assertTrue(self.is_rb_tree_valid(tree))

        # assert root is black
        tree = self.create_tree(xrange(1, 8))
        tree.root.color = Color.RED
        self.assertFalse(self.is_rb_tree_valid(tree))

        # assert equal black height
        tree = self.create_tree(xrange(1, 8))
        tree.root.left.color = Color.RED
        self.assertFalse(self.is_rb_tree_valid(tree))

        # assert rb-tree is left-leaning
        tree = self.create_tree(xrange(1, 8))
        tree.root.left.color = Color.RED
        tree.root.right.color = Color.RED
        self.assertFalse(self.is_rb_tree_valid(tree))

        # assert sequental red nodes
        tree = RBTree()
        tree.root = RBTreeNode(None, 5, Color.BLACK)
        tree.root.left = RBTreeNode(tree.root, 3, Color.RED)
        tree.root.left.left = RBTreeNode(tree.root.left, 1, Color.RED)
        self.assertFalse(self.is_rb_tree_valid(tree))

    def test_random_insert(self):
        tree = RBTree()
        for number in [random.randint(0, 2**30) for _ in xrange(1000)]:
            tree.insert(number)
        self.assertTrue(self.is_rb_tree_valid(tree))
        # self.print_tree(tree)

# logging.basicConfig(format='%(levelname)-7s %(message)s', level=logging.DEBUG)
