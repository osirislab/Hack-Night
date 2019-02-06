import bcrypt
from models import db, User, Post


def add_user(username, password):
    user = User.query.filter_by(username=username).first()
    if user:
        return (False, "User already exists")

    hashed = bcrypt.hashpw(password.encode("utf-8"), bcrypt.gensalt())

    new_usr = User(username=username, password=hashed)
    db.session.add(new_usr)
    db.session.commit()
    return (True, "User created")


def user_exists(username):
    user = User.query.filter_by(username=username).first()
    if not user:
        return (False, "User does not exist")

    return (True, "User exists")


def check_user(username, password):
    user = User.query.filter_by(username=username).first()

    if not user:
        return (False, "User does not exist")

    if bcrypt.checkpw(password.encode("utf-8"), user.password):
        return (True, user.username)
    else:
        return (False, "Invalid password")


def make_post(username, contents, preview=None):
    pass


def get_post(post_id, username):
    user = User.query.filter_by(username=username).first()
    if not user:
        return (False, "Please log in to see posts")

    post = Post.query.filter(
        (Post.id == post_id)
        & (user.username == "admin" | Post.posted_by == user.username)
    ).first()
    if post:
        return
        result = {"posted_by": post.posted_by, "id": post.id, "content": post.content}

    return (True, result)
