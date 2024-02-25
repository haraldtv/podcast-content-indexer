import os.path
import os
from worddistance import stringproximity
import string
import sys
import indexer

if ((len(sys.argv) == 3) and (sys.argv[1] == "createindex")):
    if not(os.path.isdir("./oneline")):
        print("No oneline dir")
        quit()


    dir = os.fsencode("oneline")
    numberofepisodes = 0
    for file in os.listdir(dir):
        numberofepisodes += 1
    print(numberofepisodes)
    indexer.createIndex(sys.argv[2], 10000, numberofepisodes)
    
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
        os.rename(("./oneline/"+filename), "./oneline/"+str(indx))
        print("Indexing: " + filename + " " + str(indx))
        indexer.indexFile("./oneline/"+str((indx)), sys.argv[2], (indx))
        i += 1

if ((len(sys.argv) == 4) and (sys.argv[1] == "search")):
    print(indexer.searchWord(sys.argv[2], sys.argv[3], 10))


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