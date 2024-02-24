# python bindings for indexer.c
import ctypes
import time

WORDS = 30000
EPISODES = 3

def searchWord(word, indexname, reslen):
    miscfile = open(indexname+".misc", "r")
    totalepisodes = int(miscfile.read().split()[1])
    miscfile.close()
    print(totalepisodes)
    indexlib = ctypes.CDLL("./src/indexer.so")
    charptr = ctypes.POINTER(ctypes.c_char)
    #filename = ctypes.c_char * 
    #indexlib.searchword.argtypes = ctypes.POINTER(ctypes.c_char), ctypes.POINTER(ctypes.c_char), ctypes.POINTER(ctypes.c_char)
    #indexlib.testsearch.argtypes = charptr

    indexlib.pythonsearch.restype = ctypes.POINTER(ctypes.c_int)
    result = (ctypes.c_int * reslen)()
    x = ctypes.POINTER(ctypes.c_int)
    indexlib.pythonsearch(result, reslen, indexname.encode('UTF-8'), word.encode('UTF-8'), totalepisodes)
    i = 0
    retlist = []
    while result[i] != -1 and i != reslen:
        retlist.append(result[i])
        i += 1
    return retlist

def createIndex(indexname, words, episodes):
    indexlib = ctypes.CDLL("./src/indexer.so")
    indexlib.createIndex(indexname.encode('UTF-8'), words, episodes)
    miscfile = open(indexname+".misc", "w")
    miscfile.write(str(words) + " " + str(episodes))
    miscfile.close()


def indexFile(filename, indexname, episode):
    indexlib = ctypes.CDLL("./src/indexer.so")
    miscfile = open(indexname+".misc", "r")
    totalepisodes = int(miscfile.read().split()[1])
    miscfile.close()
    print(totalepisodes)
    indexlib.indexFile(indexname.encode('UTF-8'), filename.encode('UTF-8'), episode, totalepisodes)

#createIndex("intest1.i", WORDS, EPISODES)
#indexFile("2024-2-6.txt", "intest1.i", 1)
#indexFile("2024-2-16.txt", "intest1.i", 2)
print(searchWord("elizabeth", "intest1.i", 10))
