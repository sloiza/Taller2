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
	//std::cout << "OperacionesUsuario->get" << "\n";

	//std::cout << "contenido q llega: " << contenido->getStringDeBytes() << "\n";

	ConexionServidor::BaseDeDatos::User usuario;
	usuario.setContenido(contenido->getStringDeBytes());

	std::string passwordAChequear = usuario.getPassword();

	std::string valorRecuperado = usuario.recuperar();

	usuario.setContenido(valorRecuperado);

	ConexionServidor::Respuesta respuesta;

	//std::cout << "valor recuperado: " << valorRecuperado << "\n";

	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Usuario inexistente.");
		return respuesta;
	}

	if ( usuario.getPassword().compare(passwordAChequear) != 0 )
	{
		respuesta.setEstado("mal-password");
		respuesta.setMensaje("Password invalido.");
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);

	respuesta.setEstado("ok");
	respuesta.setMensaje("Usuario recuperado correctamente!");

	return respuesta;
}
ConexionServidor::Respuesta OperacionesUsuario::post(Utiles::Bytes* contenido)
{
	ConexionServidor::BaseDeDatos::User usuarioNuevo(contenido->getStringDeBytes());
	usuarioNuevo.guardar();
	//std::cout << "OperacionesUsuario->post" << "\n";
	ConexionServidor::Respuesta respuesta;

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
