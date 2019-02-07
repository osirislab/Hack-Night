from model import db, Post


def make_post(session_id, content):
    new_post = Post(content=content, session_id=session_id)
    db.session.add(new_post)
    db.session.commit()
    return new_post.id


def get_post(session_id, post_id):
    if session_id == "botuser":
        post = Post.query.filter_by(id=post_id).first()
    else:
        post = Post.query.filter_by(id=post_id, session_id=session_id).first()
    if not post:
        return (False, None)

    return (True, post.content)


def get_posts(session_id):
    posts = Post.query.filter_by(session_id=session_id).all()
    return [{"content": post.content, "id": post.id} for post in posts]
