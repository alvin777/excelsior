import unittest

from lexer import *


class TestOpenAddressingHashMap(unittest.TestCase):
    def test_simple_expression(self):
        lexer = Lexer("2+2")

        self.assertEqual((TOKEN_INTEGER, 2), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_INTEGER, 2), lexer.get_next_token())

    def test_integers(self):
        lexer = Lexer("22 2\t\t\t   222")

        self.assertEqual((TOKEN_INTEGER, 22), lexer.get_next_token())
        self.assertEqual((TOKEN_INTEGER, 2), lexer.get_next_token())
        self.assertEqual((TOKEN_INTEGER, 222), lexer.get_next_token())

    def test_operators(self):
        lexer = Lexer("+ +2 ++ +* * *22 *+")

        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_INTEGER, 2), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())
        self.assertEqual((TOKEN_MUL_OP, '*'), lexer.get_next_token())
        self.assertEqual((TOKEN_MUL_OP, '*'), lexer.get_next_token())
        self.assertEqual((TOKEN_MUL_OP, '*'), lexer.get_next_token())
        self.assertEqual((TOKEN_INTEGER, 22), lexer.get_next_token())
        self.assertEqual((TOKEN_MUL_OP, '*'), lexer.get_next_token())
        self.assertEqual((TOKEN_ADD_OP, '+'), lexer.get_next_token())

    def test_parenthesis(self):
        lexer = Lexer("()(()))(")

        self.assertEqual((TOKEN_OPEN_PAR,  '('), lexer.get_next_token())
        self.assertEqual((TOKEN_CLOSE_PAR, ')'), lexer.get_next_token())
        self.assertEqual((TOKEN_OPEN_PAR,  '('), lexer.get_next_token())
        self.assertEqual((TOKEN_OPEN_PAR,  '('), lexer.get_next_token())
        self.assertEqual((TOKEN_CLOSE_PAR, ')'), lexer.get_next_token())
        self.assertEqual((TOKEN_CLOSE_PAR, ')'), lexer.get_next_token())
        self.assertEqual((TOKEN_CLOSE_PAR, ')'), lexer.get_next_token())
        self.assertEqual((TOKEN_OPEN_PAR,  '('), lexer.get_next_token())
