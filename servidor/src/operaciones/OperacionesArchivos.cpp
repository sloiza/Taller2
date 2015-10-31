/*
 * OperacionesArchivos.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesArchivos.h"

using namespace ConexionServidor::Operaciones;

OperacionesArchivos::OperacionesArchivos() {}

OperacionesArchivos::~OperacionesArchivos() {}

ConexionServidor::Respuesta OperacionesArchivos::delet(std::string contenido)
{
	std::cout << "OperacionesArchivos->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::get(std::string contenido)
{
	std::cout << "OperacionesArchivos->get" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::post(std::string contenido)
{
	std::cout << "OperacionesArchivos->post" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::put(std::string contenido)
{
	std::cout << "OperacionesArchivos->put" << "\n";
}

void OperacionesArchivos::imprimir()
{
	std::cout << "archivos\n";
}

