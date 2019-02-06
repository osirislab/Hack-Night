FROM ubuntu:18.04

MAINTAINER Ghost

RUN apt-get update -y && \
    apt-get install -y python-pip python-dev

# We copy just the requirements.txt first to leverage Docker cache
COPY ./requirements.txt /app/requirements.txt
COPY flag.txt /flag.txt

WORKDIR /app

RUN pip install -r requirements.txt

COPY /site /app
EXPOSE 5000

ENTRYPOINT [ "python" ]

CMD [ "app.py" ]
