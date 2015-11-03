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

ConexionServidor::Respuesta OperacionCompartirCarpeta::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionCompartirCarpeta->delete" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::get(Utiles::Bytes* contenido)
{
	std::cout << "OperacionCompartirCarpeta->get" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::post(Utiles::Bytes* contenido)
{
	std::cout << "OperacionCompartirCarpeta->post" << "\n";
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::put(Utiles::Bytes* contenido)
{
	std::cout << "OperacionCompartirCarpeta->put" << "\n";
}

void OperacionCompartirCarpeta::imprimir()
{
	std::cout << "compartirCarpeta\n";
}
