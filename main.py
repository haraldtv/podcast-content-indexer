import os.path
import os
from worddistance import stringproximity
import string
import sys
import indexer
import time
import pickle

# main.py createindex {indexname}
if ((len(sys.argv) == 3) and (sys.argv[1] == "createindex")):
    if not(os.path.isdir("./oneline")):
        print("No oneline dir")
        quit()
    if not(os.path.isdir("./indextemp")):
        os.mkdir("./indextemp")

    dir = os.fsencode("oneline")
    numberofepisodes = 0
    for file in os.listdir(dir):
        numberofepisodes += 1
    print(numberofepisodes)
    indexer.createIndex(sys.argv[2], 10000, numberofepisodes)

    numberass = dict()
    
    i = 1
    for file in os.listdir(dir):
        indx = (numberofepisodes-(i-1))
        print(indx)
        filename = os.fsdecode(file)

        currentfile = open("oneline/" + filename, "r+")
        str1 = currentfile.read().replace('\n', " ")
        for punctuation in string.punctuation:
            str1 = str1.replace(punctuation, '')
        str1 = str1.lower()
        currentfile.seek(0)
        currentfile.write(str1)
        currentfile.close()

        tempfile = open("./indextemp/tmp", "w")
        str1 = ' '.join(set(str1.split()))
        tempfile.write(str1)
        tempfile.close()

        numberass[indx] = filename
        os.rename(("./oneline/"+filename), "./oneline/"+str(indx))
        print("Indexing: " + filename + " " + str(indx))
        indexer.indexFile("./indextemp/tmp", sys.argv[2], (indx))
        i += 1
    #miscfile = open("findx.i.misc")
    with open(sys.argv[2]+".ass", "wb") as assfile:
        pickle.dump(numberass, assfile)

if ((len(sys.argv) == 4) and (sys.argv[1] == "searchword")):
    start = time.time()
    print(indexer.searchWord(sys.argv[2], sys.argv[3], 10))
    end = time.time()
    print(end-start)

if ((len(sys.argv) == 4) and (sys.argv[1] == "searchmultiple")):
    print(indexer.searchMulti(sys.argv[3], sys.argv[2], 10))

if ((len(sys.argv) == 4) and (sys.argv[1] == "searchprox")):
    filelist = indexer.searchMulti(sys.argv[3], sys.argv[2], 10)
    maxlist = []
    for fi in filelist:
        doc = open("./oneline/"+str(fi), "r").read()
        maxlist.append([stringproximity(doc, sys.argv[2]), fi])
        # print(str(fi) + ": " + str(stringproximity(doc, sys.argv[2])))
    print(maxlist)
    maxlist.sort()
    with open("findx.i.ass", "rb") as assfile:
        assdict = pickle.load(assfile)
    print([assdict[i[1]] for i in maxlist])


# start = time.time()
# tempfile = open("2024-2-16.txt", "r")
# str1 = tempfile.read().split()
# print(len(str1))
# str1 = set(str1)
# print(len(str1))
# tempfile.close()
# end = time.time()
# print(end-start)
# with open("findx.i.ass", "rb") as assfile:
#     assdict = pickle.load(assfile)
# print(assdict)
# strset = set()
# for i in range(1,6):
#     with open("./oneline/"+str(i)) as file:
#         str1 = file.read().replace('\n', " ")
#         for punctuation in string.punctuation:
#             str1 = str1.replace(punctuation, '')
#         str1 = str1.split()
#         print(len(set(str1)))
#         strset.union(set(str1))
# print(len(strset))

