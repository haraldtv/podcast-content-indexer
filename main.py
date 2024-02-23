from whoosh.index import create_in
from whoosh.fields import *
from whoosh.qparser import QueryParser
from whoosh import index
import os.path

from worddistance import stringproximity
import string

import sys

def howtouse():
    print("How to use:")
    print("main.py search \"search query\"")
    print("main.py index")
    quit()

if not((len(sys.argv) >= 2)):
    howtouse()
if ((len(sys.argv) == 2) and not( (sys.argv[1] == "index") or (sys.argv[1] == "struct") or (sys.argv[1] == "init") ) ):
    howtouse()

if ((len(sys.argv) == 2) and (sys.argv[1] == "struct")):
    if not(os.path.isdir("./rawepisodes")):
        os.mkdir("./rawepisodes")
    else:
        "./rawepisodes already exists"
    if not(os.path.isdir("./transcribedata")):
        os.mkdir("./transcribedata")
    else:
        "./transcribedata already exists"
    if not(os.path.isdir("./transcribedtxt")):
        os.mkdir("./transcribedtxt")
    else:
        "./transcribedtxt already exists"

if ((len(sys.argv) == 2) and (sys.argv[1] == "init")):
    print("Are all episodes placed in ./rawepisodes?  y/n")
    inp = input("")
    if (inp == "y" or inp == "Y"):
        print("Success")
    else:
        quit()

if ((len(sys.argv) == 3) and (sys.argv[1] == "search")):
    ix = index.open_dir("indexdir")
    with ix.searcher() as searcher:
        query = QueryParser("content", ix.schema).parse(sys.argv[2])
        results = searcher.search(query, terms=True)
        for i in results:
            print(i["title"], end=" - ")
            print("Matched:", i.matched_terms)


if ((len(sys.argv) == 3) and (sys.argv[1] == "proxsearch")):
    ix = index.open_dir("indexdir")
    with ix.searcher() as searcher:
        query = QueryParser("content", ix.schema).parse(sys.argv[2])
        results = searcher.search(query, terms=True)

        for i in results:
            print(i["title"], end=" - ")
            print("Matched:", i.matched_terms)
        print(len(results))

        DISTLIMIT = 30
        max = 0
        for i in results:
            with open((i["title"] + "/" + i["title"] + ".txt"), "r") as file:
                doc = file.read().replace("\n", " ")
            max = stringproximity(doc, sys.argv[2])
            print("Maxdistance - " + i["title"]+": "+str(max))



if ((len(sys.argv) == 2) and (sys.argv[1] == "index")):
    with open("2024-2-21/2024-2-21.txt", 'r') as file:
        str1 = file.read().replace('\n', " ")
    print(type(str1))
    print(len(str1.split()))
    with open("2024-2-9/2024-2-9.txt", 'r') as file:
        str2 = file.read().replace('\n', " ")
    print(type(str2))
    print(len(str2.split()))
    with open("2024-2-16/2024-2-16.txt", 'r') as file:
        str3 = file.read().replace('\n', " ")
    print(type(str3))
    print(len(str3.split()))

    schema = Schema(title=TEXT(stored=True), content=TEXT)
    ix = create_in("indexdir", schema)
    writer = ix.writer()
    writer.add_document(title=u"2024-2-21", content=str1)
    writer.add_document(title=u"2024-2-9", content=str2)
    writer.add_document(title=u"2024-2-16", content=str3)
    writer.commit()
