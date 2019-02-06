import os
from flask import Flask

from views import views
from admin import admin_page
from models import db


def create_app():
    app = Flask(__name__)
    #    app.secret_key = os.environ.get("FLASK_SECRET_KEY", os.urandom(24))
    app.secret_key = "supersecretkey"
    app.register_blueprint(views)
    app.register_blueprint(admin_page, url_prefix="/admin")
    app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:////tmp/chal.db"
    db.init_app(app)
    with app.app_context():
        db.create_all()
    return app


app = create_app()


if __name__ == "__main__":
    app.run("0.0.0.0", port=5000)
