import unittest


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

    def search(self, node, key):
        if key in node.keys:
            return (True, node)

        child_node = self.get_child_for_key(node, key)
        if child_node is not None:
            return self.search(child_node, key)

        return (False, node)

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

        self.insert_key(target_node, key)

    def insert_key(self, node, key):
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


class TestTwoThreeTree(unittest.TestCase):
    def create_sequential_tree(self, count):
        tree = TwoThreeTree()

        for x in xrange(1, count+1):
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
