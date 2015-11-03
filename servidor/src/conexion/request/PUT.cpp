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

ConexionServidor::Respuesta PUT::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido)
{
	return operacion->put(contenido);
}

std::string PUT::impresion()
{
	return std::string("PUT");
}
