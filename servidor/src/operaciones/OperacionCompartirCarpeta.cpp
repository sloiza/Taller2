/*
 * OperacionCompartirCarpeta.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionCompartirCarpeta.h"

using namespace ConexionServidor::Operaciones;

OperacionCompartirCarpeta::OperacionCompartirCarpeta() {}

OperacionCompartirCarpeta::~OperacionCompartirCarpeta() {}

void OperacionCompartirCarpeta::delet(std::string contenido)
{
	std::cout << "OperacionCompartirCarpeta->delete" << "\n";
}
void OperacionCompartirCarpeta::get(std::string contenido)
{
	std::cout << "OperacionCompartirCarpeta->get" << "\n";
}
void OperacionCompartirCarpeta::post(std::string contenido)
{
	std::cout << "OperacionCompartirCarpeta->post" << "\n";
}
void OperacionCompartirCarpeta::put(std::string contenido)
{
	std::cout << "OperacionCompartirCarpeta->put" << "\n";
}

std::string OperacionCompartirCarpeta::impresion()
{
	return "compartirCarpeta";
}
