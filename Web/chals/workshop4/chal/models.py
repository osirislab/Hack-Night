from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()


class User(db.Model):
    __tablename__ = "user"
    username = db.Column(db.String(100), unique=True, nullable=False, primary_key=True)
    password = db.Column(db.String(100), nullable=False)


class Post(db.Model):
    __tablename__ = "post"
    id = db.Column(db.Integer, primary_key=True)
    posted_by = db.Column(db.String(100), db.ForeignKey("user.username"))
    content = db.Column(db.String(280))
    page_preview = db.Column(db.String(200))
