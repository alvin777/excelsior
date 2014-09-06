import unittest

WHITE = 0
GREY = 1
BLACK = 2


class AdjListGraph():
    def __init__(self):
        self.adj_list = {}

    def add(self, from_node, to_node):
        if from_node not in self.adj_list:
            self.adj_list[from_node] = [to_node]
        else:
            self.adj_list[from_node].append(to_node)

    def bfs(self, root):
        color = {}
        distance = {}
        current_distance = 0

        color[root] = GREY
        distance[root] = 0
        queue = [root]
        path = []

        while len(queue) > 0:
            node = queue.pop(0)
            path.append(node)

            if node in self.adj_list:
                for ref_node in self.adj_list[node]:
                    if ref_node not in color:
                        color[ref_node] = GREY
                        distance[ref_node] = distance[node] + 1
                        queue.append(ref_node)
            color[node] = BLACK

        return distance, path

    def dfs(self, root):
        color = {}
        enter_time = {}
        exit_time = {}
        time = 0

        stack = [root]
        sorted_list = []

        while len(stack):
            node = stack[-1]

            if node not in color:
                enter_time[node] = time

            color[node] = GREY

            went_down = False
            if node in self.adj_list:
                for adj_node in self.adj_list[node]:
                    if adj_node not in color:
                        stack.append(adj_node)
                        went_down = True

            if not went_down:
                color[node] = BLACK
                exit_time[node] = time
                stack.pop()
                sorted_list.append(node)

            time += 1

        # print enter_time
        # print exit_time

        # sorted_list.reverse()
        return sorted_list


class TestGraph(unittest.TestCase):
    def test_bfs(self):
        graph = AdjListGraph()      # 6 - 4 - 5 - 1
        graph.add(6, 4)             #       \   \ |
        graph.add(4, 5)             #         3 - 2
        graph.add(4, 3)
        graph.add(3, 2)
        graph.add(5, 1)
        graph.add(5, 2)

        distance_map, path = graph.bfs(6)

        self.assertEquals(6, len(distance_map))
        self.assertEquals(0, distance_map[6])
        self.assertEquals(1, distance_map[4])
        self.assertEquals(2, distance_map[5])
        self.assertEquals(2, distance_map[3])
        self.assertEquals(3, distance_map[1])
        self.assertEquals(3, distance_map[2])
        self.assertEquals([6, 4, 5, 3, 1, 2], path)

    def test_dfs(self):
        graph = AdjListGraph()      # 6 - 4 - 5 - 1
        graph.add(6, 4)             #       \   \ |
        graph.add(4, 5)             #         3 - 2
        graph.add(4, 3)
        graph.add(3, 2)
        graph.add(5, 1)
        graph.add(5, 2)

        sorted_list = graph.dfs(6)

        self.assertEquals(6, len(sorted_list))
        self.assertEquals([2,3,1,5,4,6], sorted_list)

if __name__ == '__main__':
    unittest.main()
