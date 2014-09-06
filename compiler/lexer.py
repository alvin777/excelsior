
CHAR_WHITESPACE = ' \t'
CHAR_DIGIT = '0123456789'
CHAR_ADD_OP = '+'
CHAR_MUL_OP = '*'
CHAR_OPEN_PAR = '('
CHAR_CLOSE_PAR = ')'
CHAR_EOF = '\4'

TOKEN_INTEGER = 0
TOKEN_ADD_OP = 1
TOKEN_MUL_OP = 2
TOKEN_OPEN_PAR = 3
TOKEN_CLOSE_PAR = 4
TOKEN_END = 5


class Lexer(object):
    def __init__(self, text):
        self.text = text
        self.index = 0

    def eof(self):
        return self.index >= len(self.text)

    def get_char(self):
        if self.index >= len(self.text):
            return CHAR_EOF

        return self.text[self.index]

    def read_char(self):
        self.index += 1
        if self.index >= len(self.text):
            return CHAR_EOF
        return self.text[self.index]

    def get_next_token(self):
        while not self.eof():
            c = self.get_char()

            # print '<', c

            if c in CHAR_WHITESPACE:
                self.read_char()
                while self.get_char() in CHAR_WHITESPACE:
                    self.read_char()
            elif c in CHAR_DIGIT:
                integer = c
                self.read_char()
                while self.get_char() in CHAR_DIGIT:
                    integer += self.get_char()
                    self.read_char()
                return (TOKEN_INTEGER, int(integer))
            elif c in CHAR_ADD_OP:
                self.read_char()
                return (TOKEN_ADD_OP, c)
            elif c in CHAR_MUL_OP:
                self.read_char()
                return (TOKEN_MUL_OP, c)
            elif c in CHAR_OPEN_PAR:
                self.read_char()
                return (TOKEN_OPEN_PAR, c)
            elif c in CHAR_CLOSE_PAR:
                self.read_char()
                return (TOKEN_CLOSE_PAR, c)
        return (TOKEN_END, '')
