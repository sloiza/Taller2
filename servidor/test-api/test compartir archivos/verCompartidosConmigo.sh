#!#bin/bash

curl --data-binary "{ \"mail\":\"$1\" }" -X GET "http://localhost:8080/compartirCarpeta"