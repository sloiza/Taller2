/*
 * OperacionesArchivos.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesArchivos.h"

using namespace ConexionServidor::Operaciones;

bool OperacionesArchivos::estoyEsperandoLosBytes = false;
ConexionServidor::BaseDeDatos::Archivo* OperacionesArchivos::archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo();

OperacionesArchivos::OperacionesArchivos() {}

OperacionesArchivos::~OperacionesArchivos() {}

ConexionServidor::Respuesta OperacionesArchivos::delet(std::string contenido)
{
	std::cout << "OperacionesArchivos->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::get(std::string contenido)
{
	std::cout << "OperacionesArchivos->get" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::post(std::string contenido)
{
	settearContenidoSegunFlag(contenido);

	cambiarFlag();

	resettearArchivoTemporalSegunFlag();

	std::cout << "OperacionesArchivos->post" << "\n";
	std::cout << "contenido: " << contenido << "\n";
	Respuesta respuesta;
	respuesta.setEstado("no-existe");
	respuesta.setMensaje("Mail de usuario inexistente.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::put(std::string contenido)
{
	std::cout << "OperacionesArchivos->put" << "\n";
}

void OperacionesArchivos::imprimir()
{
	std::cout << "archivos\n";
}

void OperacionesArchivos::cambiarFlag()
{
	if ( estoyEsperandoLosBytes )
	{
		estoyEsperandoLosBytes = false;
	}
	else
	{
		estoyEsperandoLosBytes = true;
	}
}

void OperacionesArchivos::settearContenidoSegunFlag(std::string contenido)
{
	if ( estoyEsperandoLosBytes )
	{
		std::cout << "ESTOY ESPERANDO LOS BYTES\n";
		archivoTemporal->setBytes( new Utiles::Bytes( (char*)contenido.c_str(), contenido.size() ) );
	}
	else
	{
		std::cout << "NOO ESTOY ESPERANDO LOS BYTES\n";
		archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo(contenido);
	}
}
void OperacionesArchivos::resettearArchivoTemporalSegunFlag()
{
	if ( estoyEsperandoLosBytes )
	{

	}
	else
	{
		archivoTemporal->guardar();
		delete archivoTemporal;
	}
}
