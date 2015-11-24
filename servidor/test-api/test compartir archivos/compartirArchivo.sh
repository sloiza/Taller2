#!#bin/bash

pathEntero=$1
dir=${pathEntero%/*}/
nombreYExt=${pathEntero##*/}
ext=${nombreYExt##*.}
nombre=${nombreYExt%.*}

curl --data-binary "{ \"nombre\":\"${nombre}\",\"extension\":\"${ext}\",\"direccion\":\"archivos/manu@gmail.com/\",\"usuarios\":[\"$2\"]}" -X POST "http://localhost:8080/compartirArchivo"