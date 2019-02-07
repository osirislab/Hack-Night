from functools import wraps
from flask import make_response

FLAG = "flag{welcome_to_csp}"


def apply_csp(f):
    @wraps(f)
    def decorated_func(*args, **kwargs):
        resp = make_response(f(*args, **kwargs))
        csp = "; ".join(
            [
                "default-src 'self' 'unsafe-inline'",
                "style-src "
                + " ".join(["'self'", "*.bootstrapcdn.com", "use.fontawesome.com"]),
                "font-src " + "use.fontawesome.com",
                "script-src "
                + " ".join(
                    [
                        "'unsafe-inline'",
                        "'self'",
                        "cdnjs.cloudflare.com",
                        "*.bootstrapcdn.com",
                        "code.jquery.com",
                    ]
                ),
                "connect-src " + "*",
            ]
        )
        resp.headers["Content-Security-Policy"] = csp

        return resp

    return decorated_func
