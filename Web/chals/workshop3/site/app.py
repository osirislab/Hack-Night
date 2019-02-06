#!/usr/bin/env python3

from flask import Flask, request, abort, render_template_string
import os.path

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    name = request.args.get('name')
    if name is not None:
        return render_template_string(open('templates/hello.html').read().format(name=name))

    return render_template_string(open('templates/index.html').read())

if __name__ == "__main__":
    app.run(host="0.0.0.0")
