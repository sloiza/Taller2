/*
 * OperacionCompartirCarpeta.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionCompartirCarpeta.h"

using namespace ConexionServidor::Operaciones;

OperacionCompartirCarpeta::OperacionCompartirCarpeta() {}

OperacionCompartirCarpeta::~OperacionCompartirCarpeta() {}

ConexionServidor::Respuesta OperacionCompartirCarpeta::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	Utiles::Log::instancia()->warn("PUT /compartirCarpeta: no implementado.", this->nombreClase() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::get(Utiles::Bytes* contenido, std::string query)
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
		Utiles::Log::instancia()->warn("No existe carpeta compartida para: " + usuario.getEmail(), this->nombreClase() );
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Mis Compartidos/ accedida correctamente!");
	Utiles::Log::instancia()->info("Acceso a 'mis compartidos' de: " + usuario.getEmail(), this->nombreClase() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::CarpetaCompartirConUsuarios carpetaYUsuarios( contenido->getStringDeBytes() );

	std::string carpeta = carpetaYUsuarios.getPathCarpeta();
	for ( std::string mailUsuario : carpetaYUsuarios.getUsuariosACompartirles() )
	{
		compartirCarpetaConUsuario( mailUsuario,  carpeta);
	}

	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta compartida correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionCompartirCarpeta::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	Utiles::Log::instancia()->warn("PUT /compartirCarpeta: no implementado.", this->nombreClase() );
	return respuesta;
}

void OperacionCompartirCarpeta::imprimir()
{
	std::cout << "compartirCarpeta\n";
}

void OperacionCompartirCarpeta::compartirCarpetaConUsuario(std::string mailUsuario, std::string carpeta )
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoDeCarpeta;

	contenidoDeCarpeta.setPath( mailUsuario + "/" + InfoOperaciones::compartidos );

	std::string valorRecuperado = contenidoDeCarpeta.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		contenidoDeCarpeta.setContenido( valorRecuperado );
	}

	contenidoDeCarpeta.agregarCarpeta( carpeta );

	contenidoDeCarpeta.guardar();
}

std::string OperacionCompartirCarpeta::nombreClase()
{
	return "OperacionCompartirCarpeta";
}
