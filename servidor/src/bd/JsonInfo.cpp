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
	this->setContenido(contenido);
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

void JsonInfo::agregarValorAAtributo(std::string campo, std::string valorAAgregar)
{
	this->raiz[campo].append(valorAAgregar);
}

void JsonInfo::borrarValorDeAtributo(std::string campo, std::string valorABorrar)
{
	std::vector<std::string> valoresViejos = this->getListaDeValorDeAtributo(campo, "valorDefault");

	this->raiz[campo].clear();

	for ( int i = 0; i < valoresViejos.size() ; i++)
	{
		if ( valoresViejos[i].compare(valorABorrar) != 0 )
		{
			this->agregarValorAAtributo(campo, valoresViejos[i]);
		}
	}
}

void JsonInfo::borrarValoresDeAtributo(std::string campo)
{
	this->raiz[campo].clear();
}

std::vector<std::string> JsonInfo::getListaDeValorDeAtributo(std::string campo, std::string valorDefault)
{
	Json::Value valueValores = this->raiz[campo];

	std::vector<std::string> valores;
	for( int i = 0; i < valueValores.size() ; i++)
	{
		valores.push_back( valueValores[i].asString() );
	}
	return valores;
}

std::string JsonInfo::getContenido()
{
	Json::StyledWriter writer;

	return writer.write(this->raiz);
}

void JsonInfo::setContenido(std::string contenido)
{
	this->limpiar();

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

void JsonInfo::limpiar()
{
	this->raiz.clear();
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
