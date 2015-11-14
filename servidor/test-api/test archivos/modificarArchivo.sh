#!#bin/bash


curl --data-binary "@pathDelArchivoARecuperar.json" -X POST "http://localhost:8080/archivos?modificar"
curl --data-binary "@$1" -X POST "http://localhost:8080/archivos?modificar"