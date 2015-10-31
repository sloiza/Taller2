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

ConexionServidor::Respuesta OperacionCompartirArchivo::delet(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->delete" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirArchivo::get(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->get" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirArchivo::post(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->post" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirArchivo::put(std::string contenido)
{
	std::cout << "OperacionCompartirArchivo->put" << "\n";
}

void OperacionCompartirArchivo::imprimir()
{
	std::cout << "compartirArchivo\n";
}


