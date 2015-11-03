#!#bin/bash

curl --data "@subirArchivoDatos.json" -X POST "http://localhost:8080/archivos"
curl --data-binary "@$1" -X POST "http://localhost:8080/archivos"