FROM ubuntu:18.04
MAINTAINER tnek
RUN apt-get update 
RUN apt-get install -y firefox python python-pip
COPY geckodriver /usr/local/bin
COPY requirements.txt .

RUN pip install -r requirements.txt

RUN pip install gunicorn

COPY chal ./


EXPOSE 5000

CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:5000", "app:app"]
