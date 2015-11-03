#!#bin/bash

curl --data "@subirArchivoDatos.json" -X POST "http://localhost:8080/archivos"
curl --data "@subirArchivoBytes.json" -X POST "http://localhost:8080/archivos"