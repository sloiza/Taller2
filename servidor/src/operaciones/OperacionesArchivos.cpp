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

void OperacionesArchivos::delet(std::string contenido)
{
	std::cout << "OperacionesArchivos->delete" << "\n";
}
void OperacionesArchivos::get(std::string contenido)
{
	std::cout << "OperacionesArchivos->get" << "\n";
}
void OperacionesArchivos::post(std::string contenido)
{
	std::cout << "OperacionesArchivos->post" << "\n";
}
void OperacionesArchivos::put(std::string contenido)
{
	std::cout << "OperacionesArchivos->put" << "\n";
}

std::string OperacionesArchivos::impresion()
{

}

