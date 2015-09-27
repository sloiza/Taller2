!#bin/bash

curl -X POST --data "datosPOST" "http://localhost:8080/verboPOST"
curl -X GET --data "datosGET" "http://localhost:8080/verboGET"
curl -X PUT --data "datosPUT" "http://localhost:8080/verboPUT"
curl -X DELETE --data "datosDELETE" "http://localhost:8080/verboDELETE"