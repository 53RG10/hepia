#!/usr/bin/env python3

import uvicorn, os, json, sys
import numpy as np
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, FileResponse
from fastapi.middleware.cors import CORSMiddleware

import ai  # file: labo3/ai.py

# Static variables definition
HOST = "127.0.0.1"
PORT = 8000
HTML_PATH = "www/index.html"
FAVICON = "www/favicon.ico"
EASEL = "www/js/easel.js"
CANVAS = "www/js/canvas.js"
CSS = "www/style/style.css"

# Initialisation de FastAPI
app = FastAPI(
    title="Labo 3", description="Number detection using neural networks.", version="1.0"
)

# For error access-control-allow-origin
origins = [
    "http://127.0.0.1",
    "http://127.0.0.1:8000",
    "http://127.0.0.1:8080",
    "http://127.0.0.1:8000/hello",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Homepage: index.html
@app.get("/")
async def read_index():
    with open(HTML_PATH) as file:
        html_content = file.read()
    return HTMLResponse(content=html_content, status_code=200)


# Easel
@app.get("/js/easel.js")
async def read_easel():
    return FileResponse(
        path=EASEL, filename="easel.js", media_type="application/javascript"
    )


# Javascript
@app.get("/js/canvas.js")
async def read_canvas():
    return FileResponse(
        path=CANVAS, filename="canvas.js", media_type="application/javascript"
    )


# Favicon
@app.get("/favicon.ico")
async def read_favicon():
    return FileResponse(path=FAVICON, filename="favicon.ico", media_type="image/x-icon")


# CSS
@app.get("/style/style.css")
async def read_style():
    return FileResponse(path=CSS, filename="style.css", media_type="text/css")


# getting drawed number
@app.post("/")
async def write_result(request: Request):

    jsonData = await request.body()
    data = json.loads(jsonData)
    imageArray = np.array(data[0])
    imageValue = data[1]

    if len(imageValue) == 1:  # for training
        ai.save(imageArray, imageValue)
    elif len(imageValue) == 0:
        result = ai.predict(imageArray)

    dictionary = dict(enumerate(result[0]))

    return json.dumps(str(dictionary), indent=4)


if __name__ == "__main__":
    try:
        train = sys.argv[1]
        try:
            t = int(train)
        except ValueError:
            print("Error with training parameter. Using pre-trained model.")
            t = 0
    except IndexError:
        print("Traning not set. Using pre-trained model.")
        t = 0

    if t == 1:
        dataset = ai.initDataset()
        ai.train(dataset)

    print("Using pre-trained model located in labo3 directory.")
    uvicorn.run(app, host=HOST, port=PORT)
