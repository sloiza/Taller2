/*
 * OperacionBusqueda.cpp
 *
 *  Created on: 17/11/2015
 *      Author: manuel
 */

#include "OperacionBusqueda.h"

using namespace ConexionServidor::Operaciones;

OperacionBusqueda::OperacionBusqueda() {}

OperacionBusqueda::~OperacionBusqueda() {}

ConexionServidor::Respuesta OperacionBusqueda::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionBusqueda::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;

	ConexionServidor::BaseDeDatos::User usuario(contenido->getStringDeBytes());
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;

	contenidoEnCarpeta.setPath( usuario.getEmail() + "/" + InfoOperaciones::carpetaArchivosPorUsuario );
	std::string valorRecuperado = contenidoEnCarpeta.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Usuario inexistente.");
		return respuesta;
	}

	std::vector<std::string> archivosAFiltrar = contenidoEnCarpeta.getArchivos();

	std::vector<std::string> archivosEncontrados;
	if ( query.compare( ConexionServidor::BaseDeDatos::ArchivoLogico::etiquetas[enumEtiquetas::NOMBRE] ) == 0 )
	{
		archivosEncontrados = buscarArchivosPorNombre( archivosAFiltrar, query );
	}
	else if ( ( query.compare( ConexionServidor::BaseDeDatos::ArchivoLogico::etiquetas[enumEtiquetas::EXTENSION] ) == 0 ) )
	{
		archivosEncontrados = buscarArchivosPorExtension( archivosAFiltrar, query );
	}
	else if ( ( query.compare( ConexionServidor::BaseDeDatos::ArchivoLogico::etiquetas[enumEtiquetas::ETIQUETA] ) == 0 ) )
	{
		archivosEncontrados = buscarArchivosPorEtiqueta( archivosAFiltrar, query );
	}
	else if ( ( query.compare( ConexionServidor::BaseDeDatos::ArchivoLogico::etiquetas[enumEtiquetas::PROPIETARIO] ) == 0 ) )
	{
		archivosEncontrados = buscarArchivosPorPropietario( archivosAFiltrar, query );
	}

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaConRecuperados;
	for ( int i = 0 ; i < archivosEncontrados.size() ; i++)
	{
		carpetaConRecuperados.agregarArchivo( archivosEncontrados[i] );
	}

	respuesta.setContenido( carpetaConRecuperados.getContenido() );
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionBusqueda::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionBusqueda::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}



void OperacionBusqueda::imprimir()
{
	std::cout << "error\n";
}
