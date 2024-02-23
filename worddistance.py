from itertools import combinations
import string

def wordproximity(str, a, b):
    str = str.lower()
    for punctuation in string.punctuation:
        str = str.replace(punctuation, '')
    if (a == b):
        return 0
    str = str.split()
    indexa = 0
    indexb = 0

    dist = len(str)

    for i in range(len(str)):
        if (str[i] == a) or (str[i] == b):
            prev = i
            break
    
    while i<len(str):
        if (str[i] == a) or (str[i] == b):
            if str[prev] != str[i] and (i-prev) < dist:
                dist = i - prev - 1
                prev = i
            else:
                prev = i
        i += 1

    return dist

def stringproximity(str, query):
    query = query.split()
    if len(query) < 2:
        return 0
    if len(query) < 3:
        return wordproximity(str, query[0], query[1])
    querypairs = list(combinations(query, 2))
    maxDistance = wordproximity(str, querypairs[0][0], querypairs[0][1])
    for i in range(1, len(querypairs)):
        if wordproximity(str, querypairs[i][0], querypairs[i][1]) > maxDistance:
            maxDistance = wordproximity(str, querypairs[i][0], querypairs[i][1])


    return maxDistance
