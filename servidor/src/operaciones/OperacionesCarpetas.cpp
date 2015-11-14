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

ConexionServidor::Respuesta OperacionesCarpetas::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Carpeta carpeta( contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;

	if ( carpeta.existeFisicamente() == false )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		std::cout << "entro a carpeta inexistente\n";
		respuesta.setEstado("carpeta-inexistente");
		respuesta.setMensaje("No existe carpeta con ese nombre.");
		return respuesta;
	}

	if ( carpeta.estaVacia() == false )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		respuesta.setEstado("carpeta-con-contenido");
		respuesta.setMensaje("No se puede eliminar carpeta con contenido.");
		return respuesta;
	}

	std::cout << "check\n";

	carpeta.eliminar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta eliminada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesCarpetas::get(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionesCarpetas->get" << "\n";
}
ConexionServidor::Respuesta OperacionesCarpetas::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Carpeta carpeta( contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;
	if ( carpeta.existeFisicamente() )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		respuesta.setEstado("carpeta-existente");
		respuesta.setMensaje("Ya existe carpeta con ese nombre.");
		return respuesta;
	}

	carpeta.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta creada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesCarpetas::put(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionesCarpetas->put" << "\n";
}

void OperacionesCarpetas::imprimir()
{
	std::cout << "carpetas\n";
}
