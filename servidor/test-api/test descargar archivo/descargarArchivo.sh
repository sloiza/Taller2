#!#bin/bash

pathEntero=$1
dir=${pathEntero%/*}/
nombreYExt=${pathEntero##*/}
ext=${nombreYExt##*.}
nombre=${nombreYExt%.*}

curl --data-binary "{ \"nombre\":\"${nombre}\",\"extension\":\"${ext}\",\"direccion\":\"archivos/manu@gmail.com/\",\"mail\":\"$2\"}" -X GET "http://localhost:8080/descargar"