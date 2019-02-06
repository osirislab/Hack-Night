FROM mattrayner/lamp:latest-1604

COPY ./html /var/www/html/

COPY ./init_db.sh /
COPY ./db.sql /
RUN chmod +x /init_db.sh

RUN sed -i '$i/init_db.sh' /create_mysql_users.sh

RUN echo "flag{squealeeeeeee}" > /flag.txt

EXPOSE 80
CMD ["/run.sh"]
