#!#bin/bash

curl --data-binary "{ \"nombre\": \"$1\", \"etiqueta\": \"vacaciones\", \"fecha_ulti_modi\": \"03112015\", \"propietario\": \"manu@gmail.com\", \"baja_logica\": \"no\", \"direccion\": \"archivos/manu@gmail.com/\" }" -X POST "http://localhost:8080/carpetas"