/*
 * POST.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "POST.h"

using namespace ConexionServidor::Request;

POST::POST() {}

POST::~POST() {}

ConexionServidor::Respuesta POST::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido, std::string query)
{
	return operacion->post(contenido, query);
}

std::string POST::impresion()
{
	return std::string("POST");
}

