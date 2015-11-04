/*
 * OperacionesUsuario.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesUsuario.h"

using namespace ConexionServidor::Operaciones;

OperacionesUsuario::OperacionesUsuario() {}

OperacionesUsuario::~OperacionesUsuario() {}

ConexionServidor::Respuesta OperacionesUsuario::delet(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesUsuario->delete" << "\n";
}
ConexionServidor::Respuesta OperacionesUsuario::get(Utiles::Bytes* contenido)
{
	ConexionServidor::BaseDeDatos::User usuario(contenido->getStringDeBytes());
	ConexionServidor::Respuesta respuesta;

	if ( existeUsuarioConLosMismosDatos(contenido->getStringDeBytes()) == false )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Usuario inexistente.");
		return respuesta;
	}

	if ( passwordValido(contenido->getStringDeBytes()) == false )
	{
		respuesta.setEstado("mal-password");
		respuesta.setMensaje("Password invalido.");
		return respuesta;
	}

	std::string valorRecuperado = usuario.recuperar();

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Usuario recuperado correctamente!");

	return respuesta;
}
ConexionServidor::Respuesta OperacionesUsuario::post(Utiles::Bytes* contenido)
{
	ConexionServidor::BaseDeDatos::User usuarioNuevo(contenido->getStringDeBytes());

	ConexionServidor::Respuesta respuesta;
	if ( existeUsuarioConLosMismosDatos(contenido->getStringDeBytes() ) )
	{
		respuesta.setEstado("ya-existe");
		respuesta.setMensaje("Mail no disponible.");
		return respuesta;
	}

	// guardo datos del usuario.
	usuarioNuevo.guardar();

	// creo la carpeta en el disco + creo y guardo los datos logicos de la carpeta.
	ConexionServidor::BaseDeDatos::Carpeta carpetaNueva;
	carpetaNueva.setNombre( usuarioNuevo.getEmail() );
	carpetaNueva.setDireccion( InfoOperaciones::carpetaRaiz );
	carpetaNueva.setPropietario( usuarioNuevo.getEmail() );
	carpetaNueva.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Registrado correctamente!");

	return respuesta;
}
ConexionServidor::Respuesta OperacionesUsuario::put(Utiles::Bytes* contenido)
{
	std::cout << "OperacionesUsuario->put" << "\n";
}

void OperacionesUsuario::imprimir()
{
	std::cout << "usuario\n";
}

bool OperacionesUsuario::existeUsuarioConLosMismosDatos(std::string contenido)
{
	ConexionServidor::BaseDeDatos::User usuario(contenido);
	std::string valorRecuperado = usuario.recuperar();

	std::cout <<"valor recupeardo: " << valorRecuperado << "\n";

	return ( valorRecuperado.compare("vacio") == 0) ? false : true;
}
bool OperacionesUsuario::passwordValido(std::string contenido)
{
	ConexionServidor::BaseDeDatos::User usuario(contenido);
	std::string passwordAChequear = usuario.getPassword();
	std::string valorRecuperado = usuario.recuperar();

	usuario.setContenido(valorRecuperado);

	return ( usuario.getPassword().compare(passwordAChequear) == 0 ) ? true :  false;
}
