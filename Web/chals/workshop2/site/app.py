from flask import Flask, request, send_file, abort
import os.path

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    if 'page' in request.args:
        page = request.args['page']
    else:
        page = 'index.html'
    page = './pages/' + page
    if not os.path.isfile(page):
        abort(404)


    return send_file(page)



if __name__ == "__main__":
    app.run(host="0.0.0.0")
