/*
 * OperacionPrincipal.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionPrincipal.h"

using namespace ConexionServidor::Operaciones;

OperacionPrincipal::OperacionPrincipal() {}

OperacionPrincipal::~OperacionPrincipal() {}

void OperacionPrincipal::delet(std::string contenido)
{
	std::cout << "OperacionPrincipal->delete" << "\n";
}
void OperacionPrincipal::get(std::string contenido)
{
	std::cout << "OperacionPrincipal->get" << "\n";
}
void OperacionPrincipal::post(std::string contenido)
{
	std::cout << "OperacionPrincipal->post" << "\n";
}
void OperacionPrincipal::put(std::string contenido)
{
	std::cout << "OperacionPrincipal->put" << "\n";
}

std::string OperacionPrincipal::impresion()
{
	return "principal";
}
