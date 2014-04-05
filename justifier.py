#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import argparse
import sys
import unittest
from collections import namedtuple

# 
# Комментарии к реализации
#
# Как правило, задача выравнивания текста решается с помощью динамического программирования,
# например, с помощью алгоритма Кнута-Пласса (Donald E. Knuth and Michael F. Plass, Software - 
# Practice and Experience 11). Однако этот алгоритм имеет сложность O(N*N), а так как в условии
# ничего не сказано про равномерность распределения пробелов по всему тексту, то можно обойтись 
# гораздо более дешевым "жадным" алгоритмом со сложностью O(N).
#
# Реализован потоковый алгоритм, при необходимости код может быть относительно легко доработан 
# для поддержки сколь угодно длинных текстов без их полной загрузки в память. В качестве языка
# реализации был выбран Python, он вполне удовлетворяет условию "любой объектно-ориентированный 
# язык". Осознанно не были использованы Python-специфичные конструкции (list comprehensions и пр.), 
# для облегчения переноса алгоритма на другие языки и демонстрации решения задачи минимальными 
# средствами.
#
# В условиях задачи есть некоторое противоречие. Сказано, что окончанием абзаца считается строка, 
# которая заканчивается на соответствующие знаки пунктуации, абзац из одной строки длиной менее 
# половины N — это заголовок. При этом в примере первая строка "Lorem ipsum" считается абзацем, 
# но не заканчивается знаком пунктуации.
#
# Кроме того, строка
# "consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum"
# умещается в 80 символов, однако в примере слово cillum переносится на следующую строку
#
# Приняты следующие допущения и ограничения:
# - слова, длиннее максимальной длины строки, не переносятся;
# - в длину заголовка включается отступ;
# - двойные переносы строк не объединяются;
# - соответствующими знаками пунктуации считаются '.', '?' и '!'.
#
# Для проверки алгоритма реализовано некоторое количество unit-test'ов. 
# 

def enum(**enums):
    return type('Enum', (), enums)

TokenType = enum(NONE=-1, WORD=0, NL=1, END=2)
Token = namedtuple('Token', ['type', 'beginPos', 'endPos', 'charsCount'])


def getNextToken(inputText, pos):
    wordToken = None

    processingWord = False
    wordBeginPos = -1
        
    while pos < len(inputText):
        c = inputText[pos]

        if c in [' ', '\t', '\r']:
            if processingWord:
                return Token(TokenType.WORD, wordBeginPos, pos - 1, charsCount);
        elif c == '\n':
            if processingWord:
                return Token(TokenType.WORD, wordBeginPos, pos - 1, charsCount);
            return Token(TokenType.NL, pos, pos, 1);
        else:
            if not processingWord:
                processingWord = True
                wordBeginPos = pos
                charsCount = 0

            if ((ord(c) & 0x80) == 0) or \
               ((ord(c) >> 6) == 0x2):
                charsCount += 1

        pos += 1

    if processingWord:
        return Token(TokenType.WORD, wordBeginPos, pos - 1, charsCount);

    return Token(TokenType.END, pos, pos, 0);


#
# Метод возвращает строку, выровненную по maxLineWidth с учетом признака красной строки (firstLine) и
# размера отступа
#

def justifyLine(inputText, maxLineWidth, lineLength, lineWordsCount, firstLine, indentWidth, lineTokensList):
    justifiedLine = ""

    if args.debug:
        print "      justifyLine, lineWordsCount: %d, lineTokensList: %s, maxLineWidth: %d, lineLength: %d, lineWordsCount: %d" % (lineWordsCount, [inputText[lineToken.beginPos:lineToken.endPos+1] for lineToken in lineTokensList], maxLineWidth, lineLength, lineWordsCount)

    if firstLine: 
        justifiedLine += ' ' * indentWidth

    if lineWordsCount == 1:
        justifiedLine += inputText[lineTokensList[0].beginPos:lineTokensList[0].endPos+1]
        if args.debug:
            print "      justifyLine << '%s'" % justifiedLine
        return justifiedLine

    if args.debug:
        print lineLength, maxLineWidth/2, (lineLength < (maxLineWidth/2))

    if lineLength <= maxLineWidth/2:
        spacesToInsertTotal = 0
    else:
        spacesToInsertTotal = maxLineWidth - lineLength

    # количество пробелов, которые необходимо добавить к каждому промежутку
    spacesToInsertToEach = spacesToInsertTotal // (lineWordsCount - 1)
    # количество промежутков, считая с правой стороны, к которым необходимо добавить еще 1 пробел
    spacesToInsertLeft   = spacesToInsertTotal  % (lineWordsCount - 1)

    if args.debug:
        print "      justifyLine, spacesToInsertTotal: %d, spacesToInsertToEach: %s, spacesToInsertLeft: %d" % (spacesToInsertTotal, spacesToInsertToEach, spacesToInsertLeft)


    currentWordIndex = 0
    for lineToken in lineTokensList:
        justifiedLine += inputText[lineToken.beginPos:lineToken.endPos+1]

        # не добавлять пробелы в конец
        if currentWordIndex >= lineWordsCount - 1:
            break

        # рассчитать и добавить пробелы в промежуток
        spacesToInsert = 1 + spacesToInsertToEach;
        if (currentWordIndex >= lineWordsCount - spacesToInsertLeft - 1):
            spacesToInsert += 1

        justifiedLine += ' ' * spacesToInsert

        currentWordIndex += 1

    if args.debug:
        print "      justifyLine << '%s'" % justifiedLine

    return justifiedLine


def justify(inputText, maxLineWidth=80, indentWidth = 0):
    if args.debug:
        print "justify: ", inputText

    pos = 0
    outputText = ""

    lineLength = indentWidth
    lineWordsCount = 0
    lineTokensList = []

    firstLine = True
    previousToken = None
    appendLine = False

    while True:
        token = getNextToken(inputText, pos)

        if args.debug:
            print "  next token: '%s' (%s)" % (inputText[token.beginPos:token.endPos+1], token.type)

        if token.type == TokenType.WORD:
            wordLength = token.charsCount

            if args.debug:
                print "    lineLength: %d, wordLength: %d" % (lineLength, wordLength)

            # если слово помещается в текущую строку, то добавить его в lineTokensList
            # в противном случае - создать выровненную строку по lineTokensList и добавить ее 
            # к результату

            wordLengthToCheck = wordLength
            if lineWordsCount > 0:
                wordLengthToCheck += 1 # второе и последующие слова предполагают как минимум один пробел

            if lineLength + wordLengthToCheck <= maxLineWidth:
                lineTokensList.append(token)
                lineLength += wordLengthToCheck 
                lineWordsCount += 1
            else:
                appendLine = True

        elif token.type == TokenType.NL:
            if inputText[previousToken.endPos] in ('.', '?', '!'):
                appendLine = True

            if previousToken.type == TokenType.NL:
                appendLine = True

        elif token.type == TokenType.END:
            appendLine = True


        if appendLine:
            outputText += justifyLine(inputText, maxLineWidth, lineLength, lineWordsCount, firstLine, indentWidth, lineTokensList)

            if token.type == TokenType.END:
                return outputText

            outputText += '\n'

            if token.type == TokenType.NL and previousToken.type == TokenType.NL:
                outputText += '\n'

            # инициализируем следующую строчку
            if token.type == TokenType.NL:
                lineLength = indentWidth
                lineWordsCount = 0
                lineTokensList = []
                firstLine = True                
            else:
                lineLength = wordLength
                lineWordsCount = 1
                lineTokensList = [token]
                firstLine = False

            appendLine = False

        previousToken = token
        pos = token.endPos + 1


class TestJustifier(unittest.TestCase):
    def testTokenizeWord(self):
        inputText = "123"

        token = getNextToken(inputText, 0)
        self.assertEqual(token.type, TokenType.WORD)
        self.assertEqual(token.beginPos, 0)
        self.assertEqual(token.endPos, 2)

    def testTokenizeWords(self):
        inputText = "123 456 789"

        token = getNextToken(inputText, 0)
        self.assertEqual(token, Token(TokenType.WORD, 0, 2, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.WORD, 4, 6, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.WORD, 8, 10, 3))

    def testTokenizeWordsSkipSpaces(self):
        inputText = "123   456   "

        token = getNextToken(inputText, 0)
        self.assertEqual(token, Token(TokenType.WORD, 0, 2, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.WORD, 6, 8, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.END, 12, 12, 0))

    def testTokenizeNL(self):
        inputText = "123\n456\n"

        token = getNextToken(inputText, 0)
        self.assertEqual(token, Token(TokenType.WORD, 0, 2, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.NL, 3, 3, 1))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.WORD, 4, 6, 3))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.NL, 7, 7, 1))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.END, 8, 8, 0))

    def testTokenizeWordsSkipSpaces(self):
        inputText = "123!\n  456."

        token = getNextToken(inputText, 0)
        self.assertEqual(token, Token(TokenType.WORD, 0, 3, 4))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.NL, 4, 4, 1))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.WORD, 7, 10, 4))

        token = getNextToken(inputText, token.endPos + 1)
        self.assertEqual(token, Token(TokenType.END, 11, 11, 0))

    def testJustifySimpleLine(self):
        self.assertEqual(justify("123 567 901", 6), "123\n567\n901")
        self.assertEqual(justify("123 567 901", 7), "123 567\n901")
        self.assertEqual(justify("123 567 901", 8), "123  567\n901")

    def testJustifyUtf8Line(self):
        self.assertEqual(justify("фыв апр олд", 6), "фыв\nапр\nолд")
        self.assertEqual(justify("фыв апр олд", 7), "фыв апр\nолд")
        self.assertEqual(justify("фыв апр олд", 8), "фыв  апр\nолд")

    def testJustifyIndent(self):
        self.assertEqual(justify("test simple text",  8, 4), "    test\nsimple\ntext")
        self.assertEqual(justify("test simple text",  9, 4), "    test\nsimple\ntext")
        self.assertEqual(justify("test simple text", 11, 4), "    test\nsimple text")

    def testJustifySentenceEnd(self):
        self.assertEqual(justify("Test simple.\nText",  20, 4), "    Test     simple.\n    Text")
        self.assertEqual(justify("Test simple.\nText",  16, 4), "    Test simple.\n    Text")
        self.assertEqual(justify("Test simple.\nText",  15, 4), "    Test\nsimple.\n    Text")

    def testJustifyHeader(self):
        self.assertEqual(justify("Test header",  31, 4), "    Test header")
        self.assertEqual(justify("Test header",  30, 4), "    Test header")
        self.assertEqual(justify("Test header",  29, 4), "    Test               header")

    def testFullText(self):
        inputText = \
"""Lorem ipsum

Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor
incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco
laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
cillum dolore eu fugiat nulla pariatur.
Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."""

        outputText = \
"""    Lorem ipsum
    
    Lorem ipsum dolor sit amet, consectetur adipisicing  elit,  sed  do  eiusmod
tempor incididunt ut labore et dolore magna aliqua. Ut  enim  ad  minim  veniam,
quis nostrud  exercitation  ullamco  laboris  nisi  ut  aliquip  ex  ea  commodo
consequat. Duis aute irure  dolor  in  reprehenderit  in  voluptate  velit  esse
cillum dolore eu fugiat nulla pariatur.
    Excepteur sint occaecat cupidatat non proident, sunt in  culpa  qui  officia
deserunt mollit anim id est laborum."""

        self.assertEqual(justify(inputText, 80, 4), outputText)



parser = argparse.ArgumentParser(description='Justify text')
parser.add_argument("file", nargs='?', type=argparse.FileType('r'), default=sys.stdout,
                    help="input filename")
parser.add_argument("output", nargs='?', type=argparse.FileType('w'), default=sys.stdout,
                    help="output filename")
parser.add_argument("--maxwidth", type=int, default=80,
                    help="maximum line width")
parser.add_argument("--indent", type=int, default=4,
                    help="first line indentation")
parser.add_argument("--runtests", help="run unit-tests",
                    action="store_true")
parser.add_argument("--debug", help="debug output",
                    action="store_true")
args = parser.parse_args()



if args.runtests:
    del sys.argv[1:] 
# args.debug = True
    unittest.main()
else:
    args.output.write(justify(args.file.read(), args.maxwidth, args.indent))