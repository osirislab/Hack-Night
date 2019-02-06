import requests

from selenium import webdriver
from selenium.webdriver.firefox.options import Options

from chal import BOT_USER_USERNAME, BOT_USER_PASSWORD

LINK_ELEMENT_NAME = "post-link"


def botuser(base_url):
    options = Options()
    options.headless = True
    driver = webdriver.Firefox(options=options)
    try:
        if base_url[-1] != "/":
            base_url += "/"
        url = base_url + "login"

        r = requests.post(
            url,
            data={"username": BOT_USER_USERNAME, "password": BOT_USER_PASSWORD},
            allow_redirects=False,
        )
        cookie = r.cookies.get_dict()
        driver.get(base_url)
        driver.add_cookie({"name": "session_data", "value": cookie["session_data"]})
        driver.get(base_url)
    except Exception:
        pass
    finally:
        driver.quit()
