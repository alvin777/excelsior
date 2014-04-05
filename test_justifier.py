#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import unittest

INDENT_WIDTH = 4

def enum(**enums):
    return type('Enum', (), enums)

State = enum(NONE=0, WORD=1, NONWORD=2)

class LineInfo(object):
    __slots__ = ['beginPos', 'endPos', 'wordsCount', 'indented']


#
# Обработка текста выполняется в два прохода:
# - processText - заполнение массива структур LineInfo, определяющей позиции начала и конца строк, 
#   а также количество пробелов в строке
# - do_justify - собственно, потоковое копирование текста со вставкой требуемых переносов строк и пробелов
#


# Lorem ipsum dolor sit amet consectetur adipisicing
# _                   . _ | ^          . _      |    
#
# Line
# - beginPos
# - endPos
# - wordsCount


def processText(inputText, maxLineWidth, indentWidth):
    linesInfoList = []
    lineInfo = LineInfo()
    lineInfo.beginPos    = 0
    lineInfo.wordsCount  = 0
    lineInfo.indented    = True

    pos              = indentWidth   # позиция во всем тексте
    linePos          = indentWidth   # позиция в будущей строке
    lastWordStartPos = indentWidth   # позиция начала последнего слова
    lastWordEndPos   = 0             # позиция окончания последнего слова

    # при превышении заданного размера строки, позиция окончания последнего слова 
    # записывается в lineInfo.endPos, а позиция начала последнего слова - в новый 
    # lineInfo.beginPos
    
    state            = State.NONE
    previousState    = State.NONE

    for c in inputText:
        # print pos, ': char: ', c

        if c == ' ':
            state = State.NONWORD

            if previousState == State.WORD:
                lastWordEndPos = pos - 1
                lineInfo.wordsCount += 1
                # print '* lastWordEndPos: ', lastWordEndPos

        if c != ' ':
            state = State.WORD
            if previousState == State.NONWORD:
                lastWordStartPos = pos
                if lineInfo.beginPos == -1:
                    lineInfo.beginPos = lastWordStartPos
                # print '* lastWordStartPos: ', lastWordStartPos

        if pos - lineInfo.beginPos >= maxLineWidth:
            # print '* maxLineWidth hit, lineInfo.beginPos: ', lineInfo.beginPos

            lineInfo.endPos = lastWordEndPos
            linesInfoList.append(lineInfo)

            lineInfo = LineInfo()
            if c != ' ':
                lineInfo.beginPos = lastWordStartPos
            else:
                lineInfo.beginPos = -1
            lineInfo.wordsCount = 0
            lineInfo.indented = False

        pos += 1
        previousState = state

    lineInfo.endPos = pos - 1
    linesInfoList.append(lineInfo)

    return linesInfoList

# 
# Количество пробелов, которые необходимо добавить, рассчитывается следующим образом:
# - берется разность (lineSpacesToInsertCount) требуемой ширины строки и фактической 
# - делится на количество пробелов в строке (lineInfo.wordsCount - 1)
# целая часть (spacesToAddForEachSpace) будет добавлена к каждому пробелу
# остаток определяет количество пробелов справа, к которым будет добавлен один дополнительный пробел
#

def calculate_spaces_to_add(lineInfo, maxLineWidth):
    lineWidth = lineInfo.endPos - lineInfo.beginPos + 1
    currentSpaceIndex = 0
    lineSpacesToInsertCount = maxLineWidth - lineWidth

    spacesToAddForEachSpace = 0
    extraSpaceEligibleSpaces = 0

    if lineInfo.wordsCount > 1:
        spacesToAddForEachSpace  = lineSpacesToInsertCount // (lineInfo.wordsCount - 1)
        extraSpaceEligibleSpaces = lineSpacesToInsertCount % (lineInfo.wordsCount - 1)

    return spacesToAddForEachSpace, extraSpaceEligibleSpaces


#
# При копировании символов из исходного текста применяются следующие правила
# - переносы строк не копируются
# - к пробелам добавляются дополнительные
# - при достижении расчетного конца строки (lineInfo.endPos) вставляется перенос
#

def do_justify(inputText, maxLineWidth, indentWidth, linesInfoList):
    pos          = 0
    outputString = ""

    lineIndex    = 0
    lineInfo     = linesInfoList[lineIndex]

    spacesToAddForEachSpace, extraSpaceEligibleSpaces = calculate_spaces_to_add(lineInfo, maxLineWidth)
    currentSpaceIndex = 0

    for c in inputText:

        if pos == lineInfo.beginPos and lineInfo.indented:
            outputString += ' ' * indentWidth

        if pos < lineInfo.beginPos:
            pos += 1
            continue

        if c == ' ' and pos != lineInfo.endPos:
            spacesToInsertCount = 1 + spacesToAddForEachSpace
            
            if (currentSpaceIndex > lineInfo.wordsCount - extraSpaceEligibleSpaces):
                spacesToInsertCount += 1

            outputString += ' ' * spacesToInsertCount
            
            currentSpaceIndex += 1
        elif c not in ['\r', '\n']:
            outputString += c


        if pos == lineInfo.endPos and lineIndex != len(linesInfoList) - 1:
            outputString += '\n'
            lineIndex += 1

            lineInfo = linesInfoList[lineIndex]

            currentSpaceIndex = 0
            spacesToAddForEachSpace, extraSpaceEligibleSpaces = calculate_spaces_to_add(lineInfo, maxLineWidth)

        pos += 1

    return outputString


def justify(inputText, maxLineWidth=80, indentWidth = 4):    
    linesInfoList = processText(inputText, maxLineWidth, indentWidth)

    for lineInfo in linesInfoList:
        print lineInfo.beginPos, lineInfo.endPos, lineInfo.wordsCount

    return do_justify(inputText, maxLineWidth, indentWidth, linesInfoList)

class TestSortingMethods(unittest.TestCase):
    def test_simple_sentence(self):
        self.assertEqual(justify("12345 7890 2345 7890", 11, 0), \
                                 "12345  7890\n" \
                                 "2345   7890")
        self.assertEqual(justify("12345 7890 2345 7890", 10, 0), \
                                 "12345 7890\n" \
                                 "2345  7890")
        self.assertEqual(justify("12345 7890 2345 7890", 9, 0), \
                                 "12345\n" \
                                 "7890 2345\n" \
                                 "7890")
        self.assertEqual(justify("1234 6789 1234 6789", 15, 4), \
                                 "    12345  7890\n" \
                                 "2345       7890")


        self.assertEqual(justify("Lorem ipsum dolor sit amet consectetur adipisicing", 24, 0), \
                                 "Lorem  ipsum  dolor  sit\n" \
                                 "amet         consectetur\n" \
                                 "adipisicing")


if __name__ == '__main__':
    unittest.main()