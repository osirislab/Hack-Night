FROM ubuntu:18.04
RUN apt-get update && apt-get upgrade -y
RUN apt-get install python3

WORKDIR /home/chal

COPY . ./

CMD ["socat", "-T60", "TCP-LISTEN:8000,reuseaddr,fork,su=a", "EXEC:/home/chal/main.py,stderr"]
