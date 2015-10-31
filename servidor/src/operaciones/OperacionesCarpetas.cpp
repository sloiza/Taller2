/*
 * OperacionesCarpetas.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionesCarpetas.h"

using namespace ConexionServidor::Operaciones;

OperacionesCarpetas::OperacionesCarpetas() {}

OperacionesCarpetas::~OperacionesCarpetas() {}

void OperacionesCarpetas::delet(std::string contenido)
{
	std::cout << "OperacionesCarpetas->delete" << "\n";
}
void OperacionesCarpetas::get(std::string contenido)
{
	std::cout << "OperacionesCarpetas->get" << "\n";
}
void OperacionesCarpetas::post(std::string contenido)
{
	std::cout << "OperacionesCarpetas->post" << "\n";
}
void OperacionesCarpetas::put(std::string contenido)
{
	std::cout << "OperacionesCarpetas->put" << "\n";
}

std::string OperacionesCarpetas::impresion()
{
	return "carpetas";
}
