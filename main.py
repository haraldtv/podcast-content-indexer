import os.path
from worddistance import stringproximity
import string
import sys
import indexer

if ((len(sys.argv) == 3) and (sys.argv[1] == "createindex")):
    indexer.createIndex(sys.argv[2], 20000, 2)
    if not(os.path.isdir("./oneline")):
        print("No oneline dir")
        quit()
    dir = os.fsencode("oneline")
    i = 1
    for file in os.listdir(dir):
        filename = os.fsdecode(file)
        currentfile = open("oneline/" + filename, "r+")
        str1 = currentfile.read().replace('\n', " ")
        for punctuation in string.punctuation:
            str1 = str1.replace(punctuation, '')
        str1 = str1.lower()
        currentfile.seek(0)
        currentfile.write(str1)
        currentfile.close()
        os.rename(("./oneline/"+filename), "./oneline/"+str(i))
        print("Indexing: " + str(i))
        indexer.indexFile("./oneline/"+str(i), sys.argv[2], i)
        i += 1

if ((len(sys.argv) == 4) and (sys.argv[1] == "search")):
    print(indexer.searchWord(sys.argv[2], sys.argv[3], 10))