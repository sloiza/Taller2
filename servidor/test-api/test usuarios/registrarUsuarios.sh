#!#bin/bash

curl --data-binary "usuario.json" -X POST "http://localhost:8080/usuario"
curl --data-binary "usuario2.json" -X POST "http://localhost:8080/usuario"
curl --data-binary "usuario3.json" -X POST "http://localhost:8080/usuario"
curl --data-binary "usuario4.json" -X POST "http://localhost:8080/usuario"