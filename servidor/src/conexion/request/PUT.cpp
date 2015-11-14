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

ConexionServidor::Respuesta PUT::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido, std::string query)
{
	return operacion->put(contenido, query);
}

std::string PUT::impresion()
{
	return std::string("PUT");
}
