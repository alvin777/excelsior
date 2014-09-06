from lexer import *

EXPRESSION       = 0
EXPRESSION_TAIL  = 1
TERM             = 2
TERM_TAIL        = 3
FACTOR           = 4
INTEGER          = 5
OP_ADD           = 6
OP_MUL           = 7
OPEN_PAR         = 8
CLOSE_PAR        = 9

# E -> T E'
# E' -> + T E'
#      | e
# T -> N T'
# T' -> *N T'
#      | e
# N -> (E)
#      | int


# 2 + 2
# E                              E
# T E'                       T      E'
# N T' E'                  N  T'  +   T   E'
# int T' E'               int  e     N T'  e
# int E'                            int e
# int + T E'
# int + N T' E'
# int + int T' E'
# int + int E'
# int + int


class AstNode:
    def __init__(self, type, value):
        self.type = type
        self.value = value
        self.children = []
        self.parent = None

    def add_child(self, node):
        node.parent = self
        self.children.append(node)

    def get_map(self, parent_map={}):
        node_map = {}
        parent_map[self.type] = node_map
        for child in self.children:
            child.get_map(node_map)

        return parent_map

    def __str__(self):
        s = str(self.type) + '\n'
        for child in self.children:
            s += str(child)
        return s


class Parser:
    def __init__(self):
        self.root_node = None
        self.current_node = None

    def match(self, token_type):
        if self.token[0] != token_type:
            raise 'Expected: {}, actual: {}'.format(token_type, self.token[0])

        self.token = self.lexer.get_next_token()

        # print 'self.token:', self.token

    def push(self, type, value=''):
        new_node = AstNode(type, value)
        if self.current_node:
            self.current_node.add_child(new_node)
        else:
            self.root_node = new_node
        self.current_node = new_node

    def pop(self):
        self.current_node = self.current_node.parent

    def expression(self):
        self.push(EXPRESSION)

        self.term()
        self.expression_tail()

        self.pop()

    def expression_tail(self):
        if self.token[0] == TOKEN_ADD_OP:
            self.push(EXPRESSION_TAIL)

            self.push(OP_ADD)
            self.match(TOKEN_ADD_OP)
            self.pop()
            self.term()
            self.expression_tail()

            self.pop()

    def term(self):
        self.push(TERM)

        self.factor()
        self.term_tail()

        self.pop()

    def term_tail(self):
        if self.token[0] == TOKEN_MUL_OP:
            self.push(TERM_TAIL)

            self.push(OP_MUL)
            self.match(TOKEN_MUL_OP)
            self.pop()
            self.factor()
            self.term_tail()

            self.pop()

    def factor(self):
        self.push(FACTOR)

        if self.token[0] == TOKEN_INTEGER:
            self.push(INTEGER)
            self.match(TOKEN_INTEGER)
            self.pop()
        elif self.token[0] == TOKEN_OPEN_PAR:
            self.push(TOKEN_OPEN_PAR)
            self.match(TOKEN_OPEN_PAR)
            self.pop()

            self.expression()

            self.push(TOKEN_CLOSE_PAR)
            self.match(TOKEN_CLOSE_PAR)
            self.pop()
        else:
            raise 'Expected number or ( at ...'

        self.pop()

    def parse(self, text):
        self.current_node = None
        self.lexer = Lexer(text)
        self.token = self.lexer.get_next_token()

        # print 'self.token:', self.token

        self.expression()

        # print self.root_node

        return self.root_node
