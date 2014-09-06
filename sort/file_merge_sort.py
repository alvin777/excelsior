ELEMENT_SIZE = 4


def file_merge_chunks(infile1, infile2, outfile, i, j, chunk_size, infile_size):

    max_i = min(i + chunk_size, infile_size)
    max_j = min(j + chunk_size, infile_size)

    # print "i: ", i, ", j: ", j

    infile1.seek(i, 0)
    element_i = infile1.read(ELEMENT_SIZE)
    infile2.seek(j, 0)
    element_j = infile2.read(ELEMENT_SIZE)

    while i < max_i or j < max_j:

        while (i < max_i and (element_i <= element_j or j >= max_j)):
            outfile.write(element_i)
            element_i = infile1.read(ELEMENT_SIZE)
            i += ELEMENT_SIZE

        while (j < max_j and (element_j <= element_i or i >= max_i)):
            outfile.write(element_j)
            element_j = infile2.read(ELEMENT_SIZE)
            j += ELEMENT_SIZE


def file_merge_sort(infilename, outfilename):
    chunk_size = 4
    TEMP_FILE_NAME = "temp.dat"

    with open(infilename, "r") as infile:
        infile.seek(0, 2)
        infile_size = infile.tell()
        infile.seek(0, 0)

    current_infilename = infilename
    current_outfilename = outfilename

    while chunk_size < infile_size:
        i = 0
        j = chunk_size

        # print "current_infilename: ", current_infilename, ", current_outfilename: ", current_outfilename

        with open(current_infilename, "r") as infile1, \
             open(current_infilename, "r") as infile2, \
             open(current_outfilename, "w") as outfile:

            while i < infile_size:
                file_merge_chunks(infile1, infile2, outfile, i, j, chunk_size, infile_size)

                i += chunk_size*2
                j += chunk_size*2

        # if chunk_size >= 16: break

        chunk_size *= 2

        # print "current_infilename: ", current_infilename, ", infilename: ", infilename
        if current_infilename == infilename:
            # print "*"
            current_infilename, current_outfilename = current_outfilename, TEMP_FILE_NAME
        else:
            current_infilename, current_outfilename = current_outfilename, current_infilename

    if current_outfilename == TEMP_FILE_NAME:
        os.remove(TEMP_FILE_NAME)
    else:
        os.remove(outfilename)
        os.rename(TEMP_FILE_NAME, outfilename)