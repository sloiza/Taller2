#!#bin/bash

pathEntero=$1
dir=${pathEntero%/*}/
nombreYExt=${pathEntero##*/}
ext=${nombreYExt##*.}
nombre=${nombreYExt%.*}

curl --data "{ \"nombre\":\"${nombre}\",\"direccion\":\"archivos/manu@gmail.com/\", \"mail\":\"manu@gmail.com\" }" -X PUT "http://localhost:8080/papelera"