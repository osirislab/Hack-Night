from functools import wraps

from flask import Blueprint
from flask import abort, render_template, request


admin_page = Blueprint("admin_page", __name__, template_folder="templates")


def admin_required():
    if request.remote_addr != "127.0.0.1":
        return abort(404)


@admin_page.route("/", methods=["GET", "POST"])
def info():
    if request.remote_addr != "127.0.0.1":
        return render_template("404.html")

    return render_template("admin.html")


admin_page.before_request(admin_required)
