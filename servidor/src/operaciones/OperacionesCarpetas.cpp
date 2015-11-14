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

ConexionServidor::Respuesta OperacionesCarpetas::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesCarpetas->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesCarpetas::get(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesCarpetas->get" << "\n";
}
ConexionServidor::Respuesta OperacionesCarpetas::post(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesCarpetas->post" << "\n";
}
ConexionServidor::Respuesta OperacionesCarpetas::put(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesCarpetas->put" << "\n";
}

void OperacionesCarpetas::imprimir()
{
	std::cout << "carpetas\n";
}
