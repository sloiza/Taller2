#!#bin/bash

curl --data-binary "{ \"nombre\": \"$1\", \"propietario\": \"manu@gmail.com\", \"direccion\": \"archivos/manu@gmail.com/\" }" -X DELETE "http://localhost:8080/carpetas"