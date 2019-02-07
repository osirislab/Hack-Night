import os
import requests
import traceback

from chal import FLAG
from selenium import webdriver
from selenium.webdriver.firefox.options import Options

BOT_USER_PASSWORD = os.environ.get("BOT_USER_PASSWORD", "botuserpassword")


def botuser(base_url, post_id):
    try:
        if base_url[-1] != "/":
            base_url += "/"
        url = base_url + "botlogin"

        r = requests.get(url + "?id=" + BOT_USER_PASSWORD)

        cookie = r.cookies.get_dict()

        options = Options()
        options.headless = True

        driver = webdriver.Firefox(options=options)
        driver.get(base_url)
        driver.add_cookie({"name": "session", "value": cookie["session"]})
        driver.add_cookie({"name": "flag", "value": FLAG})
        driver.get(base_url + "post?id=" + str(post_id))
        driver.quit()

    except Exception as e:
        traceback.print_exc()
