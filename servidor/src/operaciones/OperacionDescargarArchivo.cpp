/*
 * OperacionDescargarArchivo.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionDescargarArchivo.h"

using namespace ConexionServidor::Operaciones;

OperacionDescargarArchivo::OperacionDescargarArchivo() {}

OperacionDescargarArchivo::~OperacionDescargarArchivo() {}

void OperacionDescargarArchivo::delet(std::string contenido)
{
	std::cout << "OperacionDescargarArchivo->delete" << "\n";
}
void OperacionDescargarArchivo::get(std::string contenido)
{
	std::cout << "OperacionDescargarArchivo->get" << "\n";
}
void OperacionDescargarArchivo::post(std::string contenido)
{
	std::cout << "OperacionDescargarArchivo->post" << "\n";
}
void OperacionDescargarArchivo::put(std::string contenido)
{
	std::cout << "OperacionDescargarArchivo->put" << "\n";
}

std::string OperacionDescargarArchivo::impresion()
{
	return "descargar";
}
