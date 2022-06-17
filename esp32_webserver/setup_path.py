import json
import pathlib
Import("env")
cvars = env.Dictionary()

with open('../config.json', 'r') as f:
    config = json.loads(f.read())

path = pathlib.Path().resolve().parent
env.Append(EXTRA_DIR=f'{path}/{config["Folder name"]}')

