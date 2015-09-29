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

void POST::ejecutar(std::string entidad, std::string contenido)
{

}

std::string POST::impresion()
{
	return std::string("POST");
}
