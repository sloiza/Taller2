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

void GET::ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido)
{

}

std::string GET::impresion()
{
	return std::string("GET");
}
