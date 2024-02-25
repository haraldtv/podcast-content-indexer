# podcast-content-indexer
A program for transcrabing, indexing, and searching in podcast content. Written in C and python

## Requirements
### Building
- python3
- OpenAI whisper (pip3 install openai-whisper)
- gcc
### Using
-  python3

## About
This project uses OpenAI whisper to transcribe podcast episodes (or other audio) to textfiles, and then indexes them using a custom indexer written in C. The program can then search the index for episodes relevant for your search. The searching algorithm is written in a combination of C and python, and there are many improvements to come.

## Features
### C library
- Indexing of text file content (the transcribed audio)
- Checking if a file contains a specified word
- Checking what files contains a specified word
### Python script
- Call the c library functions in a nicer cli style frontend
- Search for multiple words by calling the c library multiple times
- Searching based on the proximity of keywords.
  - Checks whether a file contains the given query, and if the words are in proximity to each other. Should result in more relevant searches
Note: I'm planning on porting some of the python search functions to the C library in the future for better performance

## Performance
Will update with performance at a later time, but some very quick testing gives (10-20)s for indexing a file. About 0.0007s for looking up a word, and about 0.001s for proximity search. This is tested with only 5 episodes of about 1 hour, so it needs to be tested further with a larger, more realistic dataset for the actual numbers. These current results should give an idea of the potential performance, but they are absolutely going to change in the future (especially the indexing time).

## TODO
The most important steps at the moment are automating the transcription process fully, and implementing a few ideas for the searching algorithm. In the future the indexing of files might be multithreaded, which should improve the indexing time drastically for larger datasets.

## Use (this section is not currently being kept up to date due to rapid changes in the code)
> python3 main.py [arguments]

### Arguments
createindex
> python3 main.py createindex "indexname"

Indexes all the text files in the oneline dir (these will be altered, so make sure to keep another copy somewhere else)

---

searchword
> python3 main.py searchword "word" "indexname"

Searches for a single word in the index

---

searchprox
> python3 main.py searchprox "queries to search" "indexname

Prints a list of all the files in which all the queries were found, and the maxdistance(see worddistance.py) of every pair words of the query

