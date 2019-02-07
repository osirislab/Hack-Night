import os
import requests

from chal import FLAG
from selenium import webdriver
from selenium.webdriver.firefox.options import Options

BOT_USER_PASSWORD = os.environ.get("BOT_USER_PASSWORD", "botuserpassword")


def botuser(base_url, post_id):
    if base_url[-1] != "/":
        base_url += "/"
    url = base_url + "botlogin"

    r = requests.get(url)

    cookie = r.cookies.get_dict()

    options = Options()
    options.headless = True

    driver = webdriver.Firefox(options=options)
    driver.add_cookie({"session": cookie["session"], "flag": FLAG})
    driver.get(base_url + "post?id=" + post_id)
    driver.quit()
