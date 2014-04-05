import random
import unittest
import pprint

class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class Tree:
    def __init__(self):
        self.rootNode = None

    def addData(self, data):
        if self.rootNode is None:
            self.rootNode = TreeNode(data)
            return

        node = self.rootNode
        while node:
            if data >= node.data:
                if not node.right is None:
                    node = node.right
                else:
                    node.right = TreeNode(data)
                    return
            else:
                if not node.left is None:
                    node = node.left
                else:
                    node.left = TreeNode(data)
                    return

    def addListData(self, data):
        [self.addData(x) for x in data]

    def findNode(self, data):
        parentNode = None
        node = self.rootNode

        while node:
            if data == node.data:
                return node, parentNode
            elif data >= node.data:
                parentNode = node
                node = node.right
            else:
                parentNode = node
                node = node.left

        return None, None

    def findMax(self, node):
        while node.right:
            node = node.right

        return node

    def removeData(self, data):
        nodeToRemove, parentNode = self.findNode(data)

        # print parentNode.data, nodeToRemove.data

        if nodeToRemove.right is None and nodeToRemove.left is None:
            if nodeToRemove == parentNode.left:
                parentNode.left = None
            if nodeToRemove == parentNode.right:
                parentNode.right = None
        elif nodeToRemove.right is None:
            if nodeToRemove == parentNode.left:
                parentNode.left = nodeToRemove.left
            if nodeToRemove == parentNode.right:
                parentNode.right = nodeToRemove.left
        elif nodeToRemove.left is None:
            if nodeToRemove == parentNode.left:
                parentNode.left = nodeToRemove.right
            if nodeToRemove == parentNode.right:
                parentNode.right = nodeToRemove.right
        else: # both children
            maxLeftNode = self.findMax(nodeToRemove.left)
            data = maxLeftNode.data
            self.removeData(maxLeftNode.data)
            nodeToRemove.data = data

    def bfsGenerator(self):
        queue = []
        queue.append(self.rootNode)

        while (len(queue)):
            node = queue[0]
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
            yield node.data
            queue.remove(node)

    def dfsGenerator(self):
        node = self.rootNode
        stack = []

        while (len(stack) or node):
            if node is not None:
                stack.append(node)
                node = node.left
            else:
                node = stack.pop()
                yield node.data
                node = node.right

    def getStructure(self):
        queue = [self.rootNode]
        rootDict = {}
        parentDictQueue = [rootDict]

        while (len(queue)):
            node = queue[0]
            parentDict = parentDictQueue[0]

            emptyChildDict = {}
            parentDict[node.data] = emptyChildDict

            if node.left:
                queue.append(node.left)
                parentDictQueue.append(emptyChildDict)
            if node.right:
                queue.append(node.right)
                parentDictQueue.append(emptyChildDict)

            queue.remove(node)
            parentDictQueue.remove(parentDict)

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
        tree = Tree()
        tree.addData(1)
        self.assertEqual(tree.rootNode.data, 1)

    def test_insert3(self):
        tree = Tree()
        tree.addData(1)
        tree.addData(2)
        tree.addData(3)
        self.assertEqual(tree.rootNode.data, 1)
        self.assertEqual(tree.rootNode.right.data, 2)
        self.assertEqual(tree.rootNode.right.right.data, 3)

    def test_insert3_2(self):
        tree = Tree()
        tree.addData(2)
        tree.addData(1)
        tree.addData(3)
        self.assertEqual(tree.rootNode.data, 2)
        self.assertEqual(tree.rootNode.right.data, 3)
        self.assertEqual(tree.rootNode.left.data, 1)

    def test_removeLeaf(self):
        tree = Tree()
        tree.addData(2)
        tree.addData(1)
        tree.addData(3)
        tree.removeData(3)
        self.assertEqual(tree.rootNode.data, 2)
        self.assertEqual(tree.rootNode.right, None)
        self.assertEqual(tree.rootNode.left.data, 1)
        tree.removeData(1)
        self.assertEqual(tree.rootNode.left, None)

    def test_removeNodeWithOneChild(self):
        tree = Tree()
        tree.addData(1)
        tree.addData(2)
        tree.addData(3)
        tree.removeData(2)
        self.assertEqual(tree.rootNode.data, 1)
        self.assertEqual(tree.rootNode.right.data, 3)
        self.assertEqual(tree.rootNode.right.right, None)
        self.assertEqual(tree.rootNode.right.left, None)
        self.assertEqual(tree.rootNode.left, None)
        tree.removeData(3)
        self.assertEqual(tree.rootNode.left, None)

    def test_removeNodeWithTwoChildren(self):
        tree = Tree()
        tree.addListData([1, 10, 5, 15, 7, 3, 6])
        self.assertEqual(tree.getStructure(), { 1: { 10: { 5: { 3: {}, 
                                                                7: { 6: {}}
                                                               },
                                                           15: {}
                                                          }}})
        tree.removeData(10)
        self.assertEqual(tree.getStructure(), { 1: { 7: { 5: { 3: {}, 
                                                               6: {}}, 
                                                          15: {}}}})

    def test_BfsTraversal(self):
        tree = Tree()
        tree.addListData([2,1,3])
        resultString = ""
        for elem in tree.bfsGenerator():
            resultString = resultString + str(elem) + " "
        self.assertEqual(resultString, "2 1 3 ")

    def test_BfsTraversal2(self):
        tree = Tree()
        tree.addListData([5,4,3,2,1])
        resultString = ""
        for elem in tree.bfsGenerator():
            resultString = resultString + str(elem) + " "
        self.assertEqual(resultString, "5 4 3 2 1 ")


    def test_DfsTraversal(self):
        tree = Tree()
        tree.addListData([2,1,3])
        resultString = ""
        for elem in tree.dfsGenerator():
            resultString = resultString + str(elem) + " "
        self.assertEqual(resultString, "1 2 3 ")

    def test_DfsTraversal2(self):
        tree = Tree()
        tree.addListData([5,4,3,2,1])
        resultString = ""
        for elem in tree.dfsGenerator():
            resultString = resultString + str(elem) + " "
        self.assertEqual(resultString, "1 2 3 4 5 ")

    def test_TreeStructure(self):
        tree = Tree()
        tree.addListData([2,1,3])
        # pprint.pprint(tree.getStructure())
        self.assertEqual(tree.getStructure(), { 2: { 1: {}, 3: {} }})

    def test_TreeStructure2(self):
        tree = Tree()
        tree.addListData([5,4,3,2,1])
        self.assertEqual(tree.getStructure(), { 5: { 4: { 3: { 2: { 1: {} }}}}})

if __name__ == '__main__':
    unittest.main()