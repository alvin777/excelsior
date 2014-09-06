import random
import unittest
import pprint
import random

RED = 1; BLACK = 2;

class TreeNode:
    def __init__(self, data):
        self.data = data
        self.parent = None
        self.left = None
        self.right = None
        self.color = RED

    def __str__(self):
        return "(data: {0}, color: {1})".format(self.data, "RED" if self.color == RED else "BLACK")

class RBTree:
    def __init__(self):
        self.nilNode = TreeNode(-1)
        self.nilNode.color = BLACK
        self.rootNode = self.nilNode

    def insertData(self, data):
        newNode = TreeNode(data)
        parentNode = self.nilNode
        node = self.rootNode

        while node != self.nilNode:
            parentNode = node
            if data >= node.data:
                node = node.right
            else:
                node = node.left

        newNode.parent = parentNode

        if parentNode is self.nilNode:
            self.rootNode = newNode
        elif newNode.data < parentNode.data:
            parentNode.left = newNode
        else:
            parentNode.right = newNode

        newNode.left = self.nilNode
        newNode.right = self.nilNode
        self.insertFixup(newNode)


    def insertFixup(self, node):
        while node.parent.color == RED:
            if node.parent == node.parent.parent.left:
                uncleNode = node.parent.parent.right

                if (uncleNode.color == RED):
                    uncleNode.color = BLACK              # case 1
                    node.parent.color = BLACK            # case 1
                    node.parent.parent.color = RED       # case 1
                    node = node.parent.parent
                else: # uncle color is BLACK
                    if node == node.parent.right:
                        node = node.parent               # case 2
                        self.rotateLeft(node)            # case 2
                    node.parent.color = BLACK            # case 3
                    node.parent.parent.color = RED       # case 3
                    self.rotateRight(node.parent.parent) # case 3
            else:
                uncleNode = node.parent.parent.left

                if (uncleNode.color == RED):
                    uncleNode.color = BLACK
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    node = node.parent.parent
                else: # uncle color is BLACK
                    if node == node.parent.left:
                        node = node.parent
                        self.rotateRight(node)
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    self.rotateLeft(node.parent.parent)
        self.rootNode.color = BLACK

    def rotateLeft(self, node):
        promotedNode = node.right
        reparentedChild = promotedNode.left
        parent = node.parent

        if node == self.rootNode:
            self.rootNode = promotedNode
        elif node == parent.right:
            parent.right = promotedNode
        else:
            parent.left = promotedNode

        node.parent = promotedNode
        node.right = promotedNode.left

        if node.right != self.nilNode:
            node.right.parent = node

        promotedNode.parent = parent
        promotedNode.left = node


    def rotateRight(self, node):
        promotedNode = node.left
        reparentedChild = promotedNode.right
        parent = node.parent

        if node == self.rootNode:
            self.rootNode = promotedNode
        elif node == parent.left:
            parent.left = promotedNode
        else:
            parent.right = promotedNode

        node.parent = promotedNode
        node.left = promotedNode.right

        if node.left != self.nilNode:
            node.left.parent = node

        promotedNode.parent = parent
        promotedNode.right = node

    def transplant(self, u, v):
        if u.parent == self.nilNode:
            self.rootNode = u
        else if u == u.parent.left:
            u.parent.left = v
        else 
            u.parent.right = v
        v.p = u.p

    def remove(self, data):
        nodeToRemove = self.findNode(data)
        nodeToRemoveColor = nodeToRemove.color

        if nodeToRemove.left == self.nilNode:
            fixupNode = nodeToRemove.right
            self.transplant(nodeToRemove, fixupNode)
        else if nodeToRemove.right == self.nilNode:
            fixupNode = nodeToRemove.left
            self.transplant(nodeToRemove, fixupNode)
        else:
            promotedNode = self.findMin(nodeToRemove.right)
            nodeToRemoveColor = promotedNode.color
            fixupNode = promotedNode.right

            if promotedNode.parent == nodeToRemove:
                fixupNode.parent = promotedNode  # in case fixupNode is a nilNode
            else:
                self.transplant(promotedNode, fixupNode)
                promotedNode.right = nodeToRemove.right
                promotedNode.right.parent = promotedNode
            
            self.transplant(nodeToRemove, promotedNode)
            promotedNode.left = nodeToRemove.left
            promotedNode.left.parent = promotedNode
            promotedNode.color = nodeToRemove.color

        if nodeToRemoveColor == BLACK:
            self.removeFixup(fixupNode)

    def removeFixup(self, node):
        

    def insertList(self, data):
        [self.insertData(x) for x in data]

    def validate(self):
        # rule 2
        if self.rootNode.color == RED:
            return False, "Root should be BLACK"

        visitedNodes = []
        for node in self.dfsNodeGenerator():
            if node.left != self.nilNode and node.left.parent != node:
                return False, "Node {0} left child {1} references node {2} as parent".format(node, node.left, node.left.parent)
            if node.right != self.nilNode and node.right.parent != node:
                return False, "Node {0} right child {1} references node {2} as parent".format(node, node.right, node.right.parent)

            if node in visitedNodes:
                return False, "Node {0} visited twice".format(node)
            visitedNodes.append(node)

            # rule 4
            if node.color == RED and node.left.color != BLACK and node.right.color != BLACK:
                return False, "Node {0} is RED, children should be black, left: {1}, right: {2}".format(node, node.left, node.right)

        # TODO: validate rule 5 "black height"

        return True

    def bfsNodeGenerator(self):
        queue = []
        queue.append(self.rootNode)

        while (len(queue)):
            node = queue[0]
            if node.left != self.nilNode:
                queue.append(node.left)
            if node.right != self.nilNode:
                queue.append(node.right)
            yield node
            queue.remove(node)

    def dfsNodeGenerator(self):
        node = self.rootNode
        stack = []

        while (len(stack) or node != self.nilNode):
            if node != self.nilNode:
                stack.append(node)
                node = node.left
            else:
                node = stack.pop()
                yield node
                node = node.right        

    def getStructure(self):
        queue = [self.rootNode]
        rootDict = {}
        parentDictQueue = [rootDict]

        count = 0

        while (len(queue)):
            node = queue[0]
            parentDict = parentDictQueue[0]

            emptyChildDict = {}
            parentDict[(node.data, node.color)] = emptyChildDict

            if node.left != self.nilNode:
                queue.append(node.left)
                parentDictQueue.append(emptyChildDict)
            if node.right != self.nilNode:
                queue.append(node.right)
                parentDictQueue.append(emptyChildDict)

            queue.remove(node)
            parentDictQueue.remove(parentDict)

            count+=1
            if count > 100:
                return rootDict

        return rootDict


class TestBinaryTree(unittest.TestCase):

    def setUp(self):
        self.seq = range(10)

    def test_choice(self):
        element = random.choice(self.seq)
        self.assertTrue(element in self.seq)

    def test_sample(self):
        with self.assertRaises(ValueError):
            random.sample(self.seq, 20)
        for element in random.sample(self.seq, 5):
            self.assertTrue(element in self.seq)

    def test_insert1(self):
        tree = RBTree()
        tree.insertData(1)
        self.assertEqual(tree.validate(), True)
        self.assertEqual(tree.getStructure(), { (1, BLACK): {} })

    def test_insert3(self):
        tree = RBTree()
        tree.insertList([2, 1, 3])
        self.assertEqual(tree.validate(), True)
        self.assertEqual(tree.getStructure(), { (2, BLACK): {(1, RED): {}, (3, RED): {}} })

    def test_insert3(self):
        tree = RBTree()
        tree.insertList([1, 2, 3])
        self.assertEqual(tree.validate(), True)
        self.assertEqual(tree.getStructure(), { (2, BLACK): {(1, RED): {}, (3, RED): {}} })

    def test_insert3(self):
        tree = RBTree()
        for x in xrange(1,1000):
            tree.insertData(random.SystemRandom())
        self.assertEqual(tree.validate(), True)

    def test_removal(self):
        tree = RBTree()
        tree.insertList([1,2,3,4,5,6,7,8,9])
        self.assertEqual(tree.validate(), True)
        tree.remove(1)
        self.assertEqual(tree.validate(), True)
        tree.remove(2)
        self.assertEqual(tree.validate(), True)
        tree.remove(3)
        self.assertEqual(tree.validate(), True)
        tree.remove(4)
        self.assertEqual(tree.validate(), True)
        # self.assertEqual(tree.getStructure(), { (1, BLACK): {} })

    # def test_remove(self):
    #     tree = RBTree()
    #     tree.addData(1)
    #     self.assertEqual(tree.getStructure(), { 1: {} })
    #     tree.removeData(1)
    #     self.assertEqual(tree.getStructure(), None)

    # def test_find(self):
    #     tree = RBTree()
    #     self.assertEqual(tree.find(1), False)
    #     tree.addData(1)
    #     self.assertEqual(tree.find(1), True)

    # def test_sort(self):
    #     tree = RBTree()
    #     tree.addListData([1, 2, 3])
    #     self.assertEqual(tree.sorted(), [1, 2, 3])

if __name__ == '__main__':
    unittest.main()