import whisper
import os

def transcribe(filename):
    if not(os.path.isdir("./audiofiles")):
        #os.mkdir("./audiofiles")
        print("Error: \".audiofiles\" does not exist")
    model = whisper.load_model("base.en")
    result = model.transcribe(filename, verbose=True)
