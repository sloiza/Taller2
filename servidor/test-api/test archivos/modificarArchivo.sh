#!#bin/bash

pathEntero=$1
dir=${pathEntero%/*}/
nombreYExt=${pathEntero##*/}
ext=${nombreYExt##*.}
nombre=${nombreYExt%.*}

if [ -z "$3" ]; then
	curl -X PUT "http://localhost:8080/archivos?nombre=${nombre}&extension=${ext}&etiqueta={$2}&fecha_ulti_modi=26102015&usuario_ulti_modi=manu@gmail.com&propietario=manu@gmail.com&baja_logica=no&direccion=archivos/manu@gmail.com/"
else
	curl --data-binary "@$3" -X PUT "http://localhost:8080/archivos?nombre=${nombre}&extension=${ext}&etiqueta={$2}&fecha_ulti_modi=26102015&usuario_ulti_modi=manu@gmail.com&propietario=manu@gmail.com&baja_logica=no&direccion=archivos/manu@gmail.com/"
fi