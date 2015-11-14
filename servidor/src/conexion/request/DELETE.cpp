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

ConexionServidor::Respuesta DELETE::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido)
{
	return operacion->delet(contenido);
}


std::string DELETE::impresion()
{
	return std::string("DELETE");
}

