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
	std::cout << "OperacionCompartirArchivo->delete" << "\n";
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
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Mis Compartidos/ accedida correctamente!");
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
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirArchivo::put(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionCompartirArchivo->put" << "\n";
}

void OperacionCompartirArchivo::imprimir()
{
	std::cout << "compartirArchivo\n";
}

void OperacionCompartirArchivo::compartirArchivoConUsuario(std::string mailUsuario, std::string carpeta )
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoDeCarpeta;

	contenidoDeCarpeta.setPath( mailUsuario + "/" + InfoOperaciones::compartidos );

	std::string valorRecuperado = contenidoDeCarpeta.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		contenidoDeCarpeta.setContenido( valorRecuperado );
	}

	contenidoDeCarpeta.agregarArchivo( carpeta );

	contenidoDeCarpeta.guardar();
}
