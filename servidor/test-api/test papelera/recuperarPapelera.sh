#!#bin/bash

curl --data "{\"mail\":\"$1\"}" -X GET "http://localhost:8080/papelera"