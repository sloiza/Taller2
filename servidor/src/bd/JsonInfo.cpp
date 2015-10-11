/*
 * JsonInfo.cpp
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#include "JsonInfo.h"

using namespace ConexionServidor::BaseDeDatos;

JsonInfo::JsonInfo() {}

JsonInfo::JsonInfo(std::string contenido)
{
	this->contenido = contenido;

	Json::Reader lector;

	if ( lector.parse(contenido, this->raiz) == false )
	{
		std::string mensajeError("Error al parsear contenido json: ");
		mensajeError += lector.getFormatedErrorMessages();
		Utiles::Log::instancia()->info(mensajeError, "JsonInfo");
	}
}

JsonInfo::~JsonInfo() {}

std::string JsonInfo::getAtributo(std::string campo, std::string valorDefault)
{
	return raiz.get(campo, valorDefault).asString();
}

std::string JsonInfo::getContenido()
{
	return this->contenido;
}
