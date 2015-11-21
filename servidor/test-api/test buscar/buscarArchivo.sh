#!#bin/bash


curl --data-binary "@$1" -X GET "http://localhost:8080/buscar?archivoSubido"