import xml.etree.ElementTree as ET
import sys
import os
import shutil
from concurrent.futures import ThreadPoolExecutor
import requests

def downloadEpisode(url, filename):
    response = requests.get(url)
    with open(filename, mode="wb") as file:
        file.write(response.content)
    print("Downloaded: " + filename)
    file.close()


def getEpisodeLinks(link):
    tree = ET.parse(link)
    root = tree.getroot()

    channel = root.find("channel")

    chan = list()
    chan.append(channel.find("title").text.replace(" ", "_"))

    # print("----------------------------------------")
    for episode in channel.findall("item"):
        ep = dict()
        ep["title"] = episode.find("title").text.replace(" ", "_")
        ep["pubdate"] = episode.find("pubDate").text
        ep["url"] = episode.find("enclosure").attrib.get("url")
        # print(ep["title"])
        # print(episode.find("pubDate").text)
        # print(episode.find("enclosure").attrib.get("url"))
        # print("----------------------------------------")
        chan.append(ep)
    
    return chan

def cli(link=""):
    LISTFLAG = "-l"
    DOWNLOADFLAG = "-d"
    if len(sys.argv) <= 1:
        print("Please enter arguments")
    if "-l" in sys.argv:
        channel = getEpisodeLinks(sys.argv[sys.argv.index("-l") + 1])
        print()
        print("----------------------------------------")
        for episode in channel:
            print(episode["title"])
            print(episode["pubdate"])
            print(episode["url"])
            print("----------------------------------------")
    if DOWNLOADFLAG in sys.argv:
        print("-- Download --")
        channel = getEpisodeLinks(sys.argv[sys.argv.index(DOWNLOADFLAG) + 1])

        # Create folder structure if not already created
        if not(os.path.isdir("./" + str(channel[0]))):
            print("No path: ./" + channel[0])
            print("Creating path")
            os.makedirs("./" + str(channel[0]))
            os.makedirs("./" + str(channel[0]) + "/episodes")
            shutil.copyfile(sys.argv[sys.argv.index(DOWNLOADFLAG) + 1], ("./" + channel[0] + "/" + channel[0] + ".xml"))

        # Get links and names for downloading
        urls = []
        names = []
        for i in range(1, len(channel)):
            urls.append(channel[i]["url"])
            name = str("./" + channel[0] + "/episodes/" + channel[i]["title"] + ".mp3")
            names.append(name)
        print(names)
        # Start downloads
        # with ThreadPoolExecutor() as executor:
        #    executor.map(downloadEpisode, urls, names)
        downloadEpisode(urls[0], names[0])

        # print()
        # print("----------------------------------------")
        # for episode in channel:
        #     print(episode["title"])
        #     print(episode["pubdate"])
        #     print(episode["url"])
        #     print("----------------------------------------")


cli()
# channel = getEpisodeLinks("/Users/harald/Documents/Podcast/ezra_klein.xml")
# print(channel[0])