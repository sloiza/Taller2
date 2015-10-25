/*
 * JsonInfo.cpp
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#include "JsonInfo.h"

using namespace ConexionServidor::BaseDeDatos;

JsonInfo::JsonInfo() : error(false) {}

JsonInfo::JsonInfo(std::string contenido) : error(false)
{
	this->contenido = contenido;

	Json::Reader lector;

	if ( lector.parse(contenido, this->raiz) == false )
	{
		std::string mensajeError("Error al parsear contenido json: ");
		mensajeError += lector.getFormatedErrorMessages();
		Utiles::Log::instancia()->info(mensajeError, "JsonInfo");
		this->error = true;
	}
}

JsonInfo::~JsonInfo() {}

std::string JsonInfo::getAtributo(std::string campo, std::string valorDefault)
{
	return this->raiz.get(campo, valorDefault).asString();
}

void JsonInfo::setAtributo(std::string campo, std::string valorNuevo)
{
	this->raiz[campo] = valorNuevo;
}

std::string JsonInfo::getContenido()
{
	return this->contenido;
}

void JsonInfo::setContenido(std::string contenido)
{
	this->contenido = contenido;
}

bool JsonInfo::estadoOk()
{
	return !this->error;
}

void JsonInfo::imprimir()
{
	Json::StyledWriter writer;

	std::cout << writer.write(this->raiz) << "\n";
}
