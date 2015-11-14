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

ConexionServidor::Respuesta OperacionDescargarArchivo::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionDescargarArchivo->delete" << "\n";
}
ConexionServidor::Respuesta OperacionDescargarArchivo::get(Utiles::Bytes* contenido)
{
	std::cout << "OperacionDescargarArchivo->get" << "\n";
}
ConexionServidor::Respuesta OperacionDescargarArchivo::post(Utiles::Bytes* contenido)
{
	std::cout << "OperacionDescargarArchivo->post" << "\n";
}
ConexionServidor::Respuesta OperacionDescargarArchivo::put(Utiles::Bytes* contenido)
{
	std::cout << "OperacionDescargarArchivo->put" << "\n";
}

void OperacionDescargarArchivo::imprimir()
{
	std::cout << "descargar\n";
}
