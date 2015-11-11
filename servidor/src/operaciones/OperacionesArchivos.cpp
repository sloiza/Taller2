/*
 * OperacionesArchivos.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesArchivos.h"

using namespace ConexionServidor::Operaciones;

bool OperacionesArchivos::estoyEsperandoLosBytes = false;
bool OperacionesArchivos::error = false;
ConexionServidor::BaseDeDatos::Archivo* OperacionesArchivos::archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo();

OperacionesArchivos::OperacionesArchivos() {}

OperacionesArchivos::~OperacionesArchivos() {}

ConexionServidor::Respuesta OperacionesArchivos::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesArchivos->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesArchivos::get(Utiles::Bytes* contenido)
{
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

	Respuesta respuesta = respuestaSegunFlag();

	resettearArchivoTemporalSegunFlag();

	cambiarFlag();

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
	{// estaba esperando q me lleguen los bytes para escribir el archivo fisicamente. entonces los recibo y los escribo y dejo de esperarlos.
		archivoTemporal->setBytes( contenido );

		if ( error )
		{// si hubo error en la llamada anterior, no escribo ni guardo nada.
			return;
		}

		archivoTemporal->guardar();
		agregarArchivoALaListaDeArchivosPorCarpeta( archivoTemporal->getContenido() );
	}
	else
	{// no estaba esperando bytes, es decir q ahora inicio los datos logicos y me qedo esperando los bytes.
		archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo(contenido->getStringDeBytes());
	}
}
void OperacionesArchivos::resettearArchivoTemporalSegunFlag()
{
	if ( estoyEsperandoLosBytes )
	{// si estaba esperando los bytes, entonces termino la operacion. libero la memoria del archivo temporal.
		delete archivoTemporal;
	}
	else
	{// si no estaba esperando los bytes no hago nada, solo espero a la proxima llamada q me llegan los bytes.

	}
}
ConexionServidor::Respuesta OperacionesArchivos::respuestaSegunFlag()
{
	ConexionServidor::Respuesta respuesta;
	if ( estoyEsperandoLosBytes )
	{// si estaba esperando los bytes, aviso si escribo el archivo fiscamente o no, segun haya habido error en la llamada anterior.

		if ( archivoTemporal->existeFisicamente() && archivoTemporal->contenidoValido() && error == false )
		{//
			respuesta.setEstado("ok");
			respuesta.setMensaje("Bytes de archivo escritos correctamente!");
		}
		else
		{
			respuesta.setEstado("error");
			respuesta.setMensaje("No se guardo fisicamente el archivo.");
		}
	}
	else
	{// si no estaba esperando los bytes, cheqeo q los datos logicos sean validos.
		if ( archivoTemporal->existeFisicamente() )
		{// si ya existe un archivo con el mismo path, aviso q ya existe.
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
	return respuesta;
}

void OperacionesArchivos::agregarArchivoALaListaDeArchivosPorCarpeta(std::string contenido)
{
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoLogico(contenido);

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico.getDireccion() );

	std::string valorRecuperado = contenidoEnCarpeta.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenidoEnCarpeta.setContenido(valorRecuperado);
	}

	contenidoEnCarpeta.agregarArchivo( archivoLogico.getNombreYExtension() );

	contenidoEnCarpeta.guardar();
}

