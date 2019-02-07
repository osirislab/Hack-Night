import os
import uuid

from flask import Flask, request, render_template
from flask import session, redirect, abort

from chal_visitor import botuser, BOT_USER_PASSWORD
from chal import apply_csp

from db import db, get_post, get_posts, make_post


def create_app():
    app = Flask(__name__)
    app.secret_key = os.environ.get("FLASK_SESSION_KEY", "someappsecretkey")
    app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:////tmp/chal.db"
    db.init_app(app)
    with app.app_context():
        db.create_all()
    return app


app = create_app()


@app.route("/post")
@apply_csp
def view_post():
    if "uuid" not in session:
        abort(404)

    post_id = request.args.get("id", None)
    if not post_id or not post_id.isdigit():
        abort(404)

    post_id = int(post_id)
    ok, contents = get_post(session["uuid"], post_id)
    if not ok:
        abort(404)

    return render_template("post.html", contents=contents, post_id=post_id)


@app.route("/report")
def report():
    post_id = request.args.get("id", None)
    if not post_id or not post_id.isdigit():
        abort(404)

    post_id = int(post_id)
    botuser("http://127.0.0.1:5000", post_id)
    return redirect("/")


@app.route("/botlogin")
def botlogin():
    secret_creds = request.args.get("id", None)
    if secret_creds != BOT_USER_PASSWORD:
        abort(404)

    session["uuid"] = "botuser"
    return "ok"


@app.route("/", methods=["GET", "POST"])
@apply_csp
def index():
    if request.method == "POST":
        if not "uuid" in session:
            session["uuid"] = str(uuid.uuid4())

        content = request.form.get("content")[:280]
        post_id = make_post(session["uuid"], content)
        return redirect("/post?id=" + str(post_id))

    posts = []
    if "uuid" in session:
        posts = get_posts(session["uuid"])

    return render_template("index.html", posts=posts)


if __name__ == "__main__":
    app.run("0.0.0.0", port=5000, debug=True)
