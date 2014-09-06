#!/usr/bin/env python

import os
import array
import argparse

from quick_sort import quick_sort,leaf_insertion_sort,splitByMedian
from radix_sort import radix_sort

class Stream:
    def __init__(self,streamFile, filePos, fileEndPos, wordSize = 4, bufferSize = 1024):
        self.file = streamFile
        self.filePos = filePos
        self.fileEndPos = fileEndPos
        self.wordSize = wordSize
        self.word = ""
        self.buffer = array.array('B')
        self.bufferPos = 0 
        self.bufferSize = bufferSize

        if self.filePos + self.wordSize <= self.fileEndPos: 
            self.file.seek(self.filePos)
            self.bufferSize = min(self.bufferSize, self.fileEndPos - self.filePos)
            self.buffer.fromfile(self.file, self.bufferSize)
            self.filePos += self.bufferSize
            self.word = self.buffer[self.bufferPos]

    def getWord(self):
        return self.word


    def next(self):
        # print "{} next before".format(self)
        self.bufferPos += self.wordSize

        if self.bufferPos >= self.bufferSize:
            if self.filePos >= self.fileEndPos:
                return False

            self.file.seek(self.filePos)
            self.bufferSize = min(self.bufferSize, self.fileEndPos - self.filePos)
            self.buffer = array.array('B')
            self.buffer.fromfile(self.file, self.bufferSize)
            self.filePos += self.bufferSize

            self.bufferPos = 0

        self.word = self.buffer[self.bufferPos]

        return True

    def __str__(self):
        return "%s %d/%d %s" % (self.file, self.filePos, self.fileEndPos, self.word.encode('hex'))


def external_merge_sort(infilename, outfilename, word_size = 4, memory_limit = 1024*1024):
    
    TEMP_FILE_NAME = "temp.dat"

    with open(infilename, "rb") as infile:
        infile.seek(0, 2)
        infile_size = infile.tell()
        infile.seek(0, 0)

        with open(TEMP_FILE_NAME, "wb+") as temp_file, \
             open(outfilename, "wb+") as out_file:

            # Phase 1: sort parts
            partsCount = 0
            while infile.tell() < infile_size:
                # print "infile.tell():", infile.tell()
                bytes_left = (infile_size - infile.tell())
                # values = array.array('I') # array of long integers
                values = array.array('B')
                values.fromfile(infile, min(memory_limit, bytes_left)/values.itemsize) # read integers

                # print "sorting part", partsCount + 1
                quick_sort(values,partition_func = splitByMedian, leaf_sort_func = leaf_insertion_sort,trace=False)
                # radix_sort(values, 256);
                # print "after sort:", values

                values.tofile(temp_file)
                partsCount += 1

            # Phase 2: n-way merge
            streamsList = []
            for partIndex in xrange(partsCount):
                streamsList.append(Stream(temp_file, partIndex*memory_limit, \
                                          min((partIndex+1)*memory_limit, infile_size), word_size))

            # for stream in streamsList:
            #     print stream

            out_buffer = array.array('B');
            current_words = [stream.getWord() for stream in streamsList];

            while len(streamsList) > 0:
                minIndex, minWord = min(enumerate(current_words), key=lambda e: e[1])
                # minStream = streamsList[0]
                # minWord   = minStream.getWord() 
                # for stream in streamsList[1:]:
                #     word = stream.getWord()
                #     # print "word: {}, minWord: {}".format(word.encode('hex'), minStream.getWord().encode('hex'))
                #     if word < minWord:
                #         minStream = stream
                #         minWord = word

                # print "writing: {}".format(minStream.getWord().encode('hex'))
                out_buffer.append(minWord)
                if out_buffer.buffer_info()[1] > 1024:
                    out_buffer.tofile(out_file)
                    out_buffer = array.array('B');
                    # out_file.write(minStream.getWord())
                
                if streamsList[minIndex].next():
                    current_words[minIndex] = streamsList[minIndex].getWord()
                else:
                    del streamsList[minIndex]
                    del current_words[minIndex]

            out_buffer.tofile(out_file)

def main():
    # if os.path.exists("small2_out.dat"):
    #     os.remove("small2_out.dat")
    # if os.path.exists("temp.dat"):
    #     os.remove("temp.dat")
    # external_merge_sort("small2.dat", "small2_out.dat", word_size = 1, memory_limit=3)
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-m', '--memory-limit', default='1048576', type=int)
    parser.add_argument('-w', '--word-size', default='1', type=int)
    parser.add_argument('file')
    parser.add_argument('outfile', nargs='?')

    args = parser.parse_args()
    print args
    if args.outfile is None:
        filename, ext = os.path.splitext(args.file)
        args.outfile = "".join([filename, "_out", ext])

    external_merge_sort(infilename = args.file, outfilename = args.outfile, \
                        word_size = args.word_size, memory_limit = args.memory_limit)

if __name__ == '__main__':
    main()