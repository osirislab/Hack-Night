#!/bin/bash

mysql -uroot -e "CREATE USER 'php'@'%' IDENTIFIED BY 'totallyasecurepassword'"
mysql -uroot -e "CREATE DATABASE php"
mysql -uroot -e "GRANT ALL PRIVILEGES ON php.* TO 'php'@'%'"

mysql -u root php < db.sql
