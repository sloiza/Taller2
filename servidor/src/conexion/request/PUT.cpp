/*
 * PUT.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "PUT.h"

using namespace ConexionServidor::Request;

PUT::PUT() {}

PUT::~PUT() {}

void PUT::ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido)
{
	//entidad->crear(contenido);
}

std::string PUT::impresion()
{
	return std::string("PUT");
}
