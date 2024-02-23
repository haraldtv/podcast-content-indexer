# podcast-indexer
Transcribing and indexing podcast content

## Requirements
- python3
- whoosh (pip3 install whoosh)
- OpenAI whisper (pip3 install openai-whisper)

## Use
> python3 main.py [arguments]

### Arguments
struct
> python3 main.py struct

Initializes required folders if they don't already exist

---

init
> python3 main.py init

Creates required folder structure in ./transcribedata for every episode placed in ./rawepisodes

---

index
> python3 main.py index

Creates a searchable index of every transcribed episode from the ./transcribedtxt folder. Requires the user to create the ./indexdir folder first

---

search
> python3 main.py search "search queries here"

Searches the index for the given search query/queries. Requires there to be an index generated
