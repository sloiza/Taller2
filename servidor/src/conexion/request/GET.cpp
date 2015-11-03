/*
 * GET.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "GET.h"

using namespace ConexionServidor::Request;

GET::GET() {}

GET::~GET() {}

ConexionServidor::Respuesta GET::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido)
{
	return operacion->get(contenido);
}

std::string GET::impresion()
{
	return std::string("GET");
}

