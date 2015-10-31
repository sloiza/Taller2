/*
 * OperacionErrorURL.cpp
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#include "OperacionErrorURL.h"

using namespace ConexionServidor::Operaciones;

OperacionErrorURL::OperacionErrorURL() {}

OperacionErrorURL::~OperacionErrorURL() {}

ConexionServidor::Respuesta OperacionErrorURL::delet(std::string contenido)
{
	std::cout << "OperacionErrorURL->delete" << "\n";
}
ConexionServidor::Respuesta OperacionErrorURL::get(std::string contenido)
{
	std::cout << "OperacionErrorURL->get" << "\n";
}
ConexionServidor::Respuesta OperacionErrorURL::post(std::string contenido)
{
	std::cout << "OperacionErrorURL->post" << "\n";
}
ConexionServidor::Respuesta OperacionErrorURL::put(std::string contenido)
{
	std::cout << "OperacionErrorURL->put" << "\n";
}

void OperacionErrorURL::imprimir()
{
	std::cout << "error\n";
}
