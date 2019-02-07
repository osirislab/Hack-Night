import os
from functools import wraps
from flask import make_response

FLAG = os.environ.get("CHALLENGE_FLAG", "flag{welcome_to_csp}")
CSP = os.environ.get("CHALLENGE_CSP", None)


def get_csp():
    if CSP is not None:
        return CSP

    csp = "; ".join(
        [
            "default-src 'self' 'unsafe-inline'",
            "script-src " + " ".join(["'unsafe-inline'", "'self'"]),
            "connect-src " + "*",
        ]
    )
    return csp


def apply_csp(f):
    @wraps(f)
    def decorated_func(*args, **kwargs):
        resp = make_response(f(*args, **kwargs))
        resp.headers["Content-Security-Policy"] = get_csp()

        return resp

    return decorated_func
