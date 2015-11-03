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

ConexionServidor::Respuesta OperacionesArchivos::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesArchivos->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::get(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesArchivos->get" << "\n";
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoLogico( contenido->getStringDeBytes() );

	std::string valorRecuperado = archivoLogico.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Archivo inexistente.");
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo recuperado correctamente!");

	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::post(Utiles::Bytes* contenido)
{
	settearContenidoSegunFlag(contenido);

	cambiarFlag();

	Respuesta respuesta = respuestaSegunFlag();

	resettearArchivoTemporalSegunFlag();

	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::put(Utiles::Bytes* contenido)
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

void OperacionesArchivos::settearContenidoSegunFlag(Utiles::Bytes* contenido)
{
	if ( estoyEsperandoLosBytes )
	{
		archivoTemporal->setBytes( contenido );
		archivoTemporal->guardar();
	}
	else
	{
		archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo(contenido->getStringDeBytes());
	}
}
void OperacionesArchivos::resettearArchivoTemporalSegunFlag()
{
	if ( estoyEsperandoLosBytes )
	{

	}
	else
	{
		delete archivoTemporal;
	}
}
ConexionServidor::Respuesta OperacionesArchivos::respuestaSegunFlag()
{
	static bool error = false;
	ConexionServidor::Respuesta respuesta;
	if ( estoyEsperandoLosBytes )
	{
		if ( archivoTemporal->existeFisicamente() )
		{
			respuesta.setEstado("archivo-existente");
			respuesta.setMensaje("Ya existe el archivo.");
			error = true;
			return respuesta;
		}
		else
		{
			error = false;
		}

		if ( archivoTemporal->contenidoValido() )
		{
			respuesta.setEstado("ok");
			respuesta.setMensaje("Metadatos de archivo reconocidos correctamente!");
			error = false;
		}
		else
		{
			respuesta.setEstado("datos-no-validos");
			respuesta.setMensaje("Metadatos no validos.");
			error = true;
		}
	}
	else
	{
		if ( archivoTemporal->existeFisicamente() && archivoTemporal->contenidoValido() && error == false )
		{
			respuesta.setEstado("ok");
			respuesta.setMensaje("Bytes de archivo escritos correctamente!");
		}
		else
		{
			respuesta.setEstado("error");
			respuesta.setMensaje("No se guardo fisicamente el archivo.");
		}
	}
	return respuesta;
}
