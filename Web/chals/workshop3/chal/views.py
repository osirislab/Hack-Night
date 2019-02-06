from functools import wraps
import requests

from flask import Blueprint
from flask import redirect, url_for, request, render_template, session, make_response

from db import add_user, check_user, user_exists, get_post

views = Blueprint("views", __name__, template_folder="templates")


def apply_csp(f):
    @wraps(f)
    def decorated_func(*args, **kwargs):
        resp = make_response(f(*args, **kwargs))

        csp = "; ".join(
            [
                "default-src 'self'",
                "style-src 'self' stackpath.bootstrapcdn.com",
                "script-src 'self' stackpath.bootstrapcdn.com cdnjs.cloudflare.com code.jquery.com",
            ]
        )

        resp.headers["Content-Security-Policy"] = csp
        return resp

    return decorated_func


def login_required(f):
    @wraps(f)
    def decorated_func(*args, **kwargs):
        uname = session.get("username")
        if not uname or not user_exists(uname):
            return redirect(url_for("views.login"))
        return f(*args, **kwargs)

    return decorated_func


@views.route("/")
@login_required
@apply_csp
def index():
    return render_template("index.html")


def get_preview(contents):
    pass


@views.route("/post", methods=["GET", "POST"])
@login_required
@apply_csp
def post():
    if request.method == "POST":
        uname = session.get("username")
        contents = request.form.get("contents")
        preview = get_preview(contents)


@views.route("/view")
@login_required
@apply_csp
def view_post():
    post_id = request.args.get("id", None)
    post = None

    if post_id is not None:
        if post_id.isdigit():
            post_id = int(post_id)

        ok, post = get_post(post_id)

    return render_template("view.html", post=post)


@views.route("/login", methods=["GET", "POST"])
def login():
    uname = session.get("username")
    if uname and user_exists(uname):
        return redirect("/")
    err = None
    if request.method == "POST":
        username = request.form.get("username", None)
        password = request.form.get("password", None)

        ok, err = check_user(username, password)
        if ok:
            session["username"] = username
            return redirect("/")

    return render_template("login.html", err=err)


@views.route("/register", methods=["GET", "POST"])
def register():
    err = None
    if request.method == "POST":
        username = request.form.get("username", None)
        password = request.form.get("password", None)
        confirm = request.form.get("confirm-password", None)
        if password != confirm:
            return render_template("register.html", err="Passwords don't match")

        ok, err = add_user(username, password)
        if ok:
            return redirect(url_for("views.login"))

    return render_template("register.html", err=err)
