#!#bin/bash

curl --data-binary "@$1" -X DELETE "http://localhost:8080/carpetas"