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

ConexionServidor::Respuesta OperacionPrincipal::delet(std::string contenido)
{
	std::cout << "OperacionPrincipal->delete" << "\n";
}
ConexionServidor::Respuesta OperacionPrincipal::get(std::string contenido)
{
	std::cout << "OperacionPrincipal->get" << "\n";
}
ConexionServidor::Respuesta OperacionPrincipal::post(std::string contenido)
{
	std::cout << "OperacionPrincipal->post" << "\n";
}
ConexionServidor::Respuesta OperacionPrincipal::put(std::string contenido)
{
	std::cout << "OperacionPrincipal->put" << "\n";
}

void OperacionPrincipal::imprimir()
{
	std::cout << "principal\n";
}
