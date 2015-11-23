#!#bin/bash

pathEntero=$1
dir=${pathEntero%/*}/
nombreYExt=${pathEntero##*/}
ext=${nombreYExt##*.}
nombre=${nombreYExt%.*}

curl --data-binary "@$1" -X POST "http://localhost:8080/archivos?nombre=${nombre}&extension=${ext}&etiqueta=imagen&fecha_ulti_modi=26102015&usuario_ulti_modi=manu@gmail.com&propietario=manu@gmail.com&baja_logica=no&direccion=archivos/manu@gmail.com/"