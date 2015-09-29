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

void DELETE::ejecutar(std::string entidad, std::string contenido)
{

}

std::string DELETE::impresion()
{
	return std::string("DELETE");
}
