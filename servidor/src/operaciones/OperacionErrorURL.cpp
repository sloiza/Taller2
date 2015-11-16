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

ConexionServidor::Respuesta OperacionErrorURL::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionErrorURL::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionErrorURL::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionErrorURL::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}

void OperacionErrorURL::imprimir()
{
	std::cout << "error\n";
}
