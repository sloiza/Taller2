/*
 * OperacionCompartirArchivo.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionCompartirArchivo.h"

using namespace ConexionServidor::Operaciones;

OperacionCompartirArchivo::OperacionCompartirArchivo() {}

OperacionCompartirArchivo::~OperacionCompartirArchivo() {}

void OperacionCompartirArchivo::delet(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->delete" << "\n";
}
void OperacionCompartirArchivo::get(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->get" << "\n";
}
void OperacionCompartirArchivo::post(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->post" << "\n";
}
void OperacionCompartirArchivo::put(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->put" << "\n";
}

std::string OperacionCompartirArchivo::impresion()
{
	return "compartirArchivo";
}


