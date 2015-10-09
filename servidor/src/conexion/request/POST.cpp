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

void POST::ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido)
{
//	ManagerBD::instancia()->modificar(this->entidad, contenido);
//
//	delete manager;
}

std::string POST::impresion()
{
	return std::string("POST");
}
