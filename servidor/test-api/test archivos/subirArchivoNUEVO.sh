#!#bin/bash

curl --data-binary "@$1" -X POST "http://localhost:8080/archivos?\{\"nombre\":\"archivoSubido\",\"extension\":\"test2\",\"etiqueta\":\"imagen\",\"fecha_ulti_modi\":\"26102015\",\"usuario_ulti_modi\":\"1234\",\"propietario\":\"manu@gmail.com\",\"baja_logica\":\"no\",\"direccion\":\"tmp/\"\}"