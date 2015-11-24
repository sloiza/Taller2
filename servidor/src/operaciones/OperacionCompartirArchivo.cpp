/*
 * OperacionCompartirArchivo.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionCompartirArchivo.h"

using namespace ConexionServidor::Operaciones;

OperacionCompartirArchivo::OperacionCompartirArchivo() {}

OperacionCompartirArchivo::~OperacionCompartirArchivo() {}

ConexionServidor::Respuesta OperacionCompartirArchivo::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	Utiles::Log::instancia()->warn("DELETE /compartirArchivo: no implementado.", this->nombreClase() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirArchivo::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuario( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoDeCarpeta;

	contenidoDeCarpeta.setPath( usuario.getEmail() + "/" + InfoOperaciones::compartidos);

	std::string valorRecuperado = contenidoDeCarpeta.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("No existe carpeta para el usuario.");
		Utiles::Log::instancia()->warn("URL no mapeada.", this->nombreClase() );
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Mis Compartidos/ accedida correctamente!");
	Utiles::Log::instancia()->info("Acceso a 'mis compartidos' de " + usuario.getEmail(), this->nombreClase() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirArchivo::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::ArchivoCompartirConUsuarios archivoYUsuarios( contenido->getStringDeBytes() );

	std::string carpeta = archivoYUsuarios.getPathArchivo();
	for ( std::string mailUsuario : archivoYUsuarios.getUsuariosACompartirles() )
	{
		compartirArchivoConUsuario( mailUsuario, carpeta );
	}

	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo compartido correctamente!");
	Utiles::Log::instancia()->info("Archivo '" + archivoYUsuarios.getPathArchivo() + "' compartido correctamente.", this->nombreClase() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirArchivo::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	Utiles::Log::instancia()->warn("PUT /compartirArchivo: no implementado.", this->nombreClase() );
	return respuesta;
}

void OperacionCompartirArchivo::imprimir()
{
	std::cout << "compartirArchivo\n";
}

void OperacionCompartirArchivo::compartirArchivoConUsuario(std::string mailUsuario, std::string archivo )
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaCompartida;

	carpetaCompartida.setPath( mailUsuario + "/" + InfoOperaciones::compartidos );

	ConexionServidor::BaseDeDatos::ArchivoLogico archivoLogico;
	archivoLogico.setPath( archivo );

	bool resCompartirArchivo = this->acciones.agregarArchivoLogicoAContenido( &archivoLogico, &carpetaCompartida );

	if ( resCompartirArchivo == false )
	{
		Utiles::Log::instancia()->warn("No se pudo compartir el archivo: '" + archivoLogico.getPath() + "'.", this->nombreClase() );
		return;
	}

	std::string valorRecuperado = archivoLogico.recuperar();
	archivoLogico.setContenido( valorRecuperado );

	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario version;
	version.setUsuario( mailUsuario );
	version.setPathArchivo( archivoLogico.getPath() );
	version.setVersion( archivoLogico.getVersion() );

	version.modificar();
}
std::string OperacionCompartirArchivo::nombreClase()
{
	return "OperacionCompartirArchivo";
}
