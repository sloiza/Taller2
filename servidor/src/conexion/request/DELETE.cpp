/*
 * DELETE.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "DELETE.h"

using namespace ConexionServidor::Request;

DELETE::DELETE() {}

DELETE::~DELETE() {}

void DELETE::ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido)
{
	//ConexionServidor::BaseDeDatos::JsonInfo* info = new ConexionServidor::BaseDeDatos::JsonInfo(contenido);
	entidad->setContenido(contenido);

	entidad->eliminar();

	//operacion->delete(contenido);
}

std::string DELETE::impresion()
{
	return std::string("DELETE");
}
