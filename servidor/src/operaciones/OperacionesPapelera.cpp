/*
 * OperacionesPapelera.cpp
 *
 *  Created on: 16/11/2015
 *      Author: manuel
 */

#include "OperacionesPapelera.h"

using namespace ConexionServidor::Operaciones;

OperacionesPapelera::OperacionesPapelera() {}

OperacionesPapelera::~OperacionesPapelera() {}

ConexionServidor::Respuesta OperacionesPapelera::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );
	std::string valorRecuperadoPapelera = papelera.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperadoPapelera.compare("vacio") != 0 )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("No existe papelera para el usuario.");
		return respuesta;
	}

	papelera.eliminarTodosLosArchivos();
	papelera.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Papelera vaciada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );

	std::string valorRecuperado = papelera.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		papelera.setContenido( valorRecuperado );
	}

	ConexionServidor::Respuesta respuesta;
	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Papelera accedida correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::put(Utiles::Bytes* contenido, std::string query)
{
	// NOTA: SI SE LLAMA A "PUT /papelera + datos.json" el archivo se restaurara, aun aunq no este en la papelera.
	// se supone que siempre "datos.json" siempre tendran datos de un archivo ubicado en la papelera.

	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoARecuperar( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );
	std::string valorRecuperadoPapelera = papelera.recuperar();

	std::cout << "papelera path papelera: " + usuarioAux.getEmail() + "/" + InfoOperaciones::papelera << "\n";

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperadoPapelera.compare("vacio") == 0 )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("No existe papelera para el usuario.");
		return respuesta;
	}
	else
	{
		papelera.setContenido( valorRecuperadoPapelera );
	}

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaOriginal;
	carpetaOriginal.setPath( archivoARecuperar.getDireccion() );
	std::string valorRecuperadoCarpeta = carpetaOriginal.recuperar();
	if ( valorRecuperadoCarpeta.compare("vacio") != 0 )
	{
		carpetaOriginal.setContenido( valorRecuperadoCarpeta );
	}

	// saco el archivo de la papelera
	papelera.eliminarArchivo( archivoARecuperar.getPath() );
	papelera.guardar();

	// sete "baja_logica" del archivo en "no", y lo agrego a la carpeta donde estaba originalmente
	archivoARecuperar.setBajaLogica( "no" );
	archivoARecuperar.guardar();
	carpetaOriginal.agregarArchivo( archivoARecuperar.getPath() );
	carpetaOriginal.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo restaurado correctamente!");
	return respuesta;
}

void OperacionesPapelera::imprimir()
{
	std::cout << "papelera\n";
}

