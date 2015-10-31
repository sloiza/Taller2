#!#bin/bash

curl --data "@data.json" -X POST "http://localhost:8080/usuario"
curl --data "datosGET" -X GET "http://localhost:8080/verboGET"
curl --data "datosPUT" -X PUT "http://localhost:8080/verboPUT"
curl --data "datosDELETE" -X DELETE "http://localhost:8080/verboDELETE"