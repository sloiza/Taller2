#!#bin/bash

curl --data-binary "@pathDelArchivoARecuperar.json" -X GET "http://localhost:8080/archivos"