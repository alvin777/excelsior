import unittest

from parser import *

# EXPRESSION
# TERM
# FACTOR
# INTEGER

class TestParser(unittest.TestCase):
    def test_simple_expression(self):
        parser = Parser()
        cst = parser.parse('2+2').get_map()
        self.assertEquals(cst, { EXPRESSION: {         # root[EXPRESSION] = expression_map; 
                                   TERM: {             #   expression_map[TERM] = .. 
                                     FACTOR: {         #
                                       INTEGER: {}
                                     }
                                   },
                                   EXPRESSION_TAIL: {  #   expression_map[EXPRESSION_TAIL] = ..
                                     OP_ADD: {
                                     },
                                     TERM: {
                                       FACTOR: {
                                         INTEGER: {}
                                       }
                                     }
                                   }
                                 }
                               })