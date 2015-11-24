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
		Utiles::Log::instancia()->warn("Usuario inexiste.", this->nombreClase() );
		return respuesta;
	}

	contenidoEnCarpeta.setContenido(valorRecuperado);

	std::vector<std::string> pathsAFiltrar = contenidoEnCarpeta.getArchivos();

	std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivosAFiltrar = this->getArchivosAFiltrar(pathsAFiltrar);

	std::vector<std::string> archivosEncontrados;
	std::vector<std::string> archivosEncontradosPorNombre = buscarArchivosPorNombre( archivosAFiltrar, query );
	std::vector<std::string> archivosEncontradosPorExtension = buscarArchivosPorExtension( archivosAFiltrar, query );
	std::vector<std::string> archivosEncontradosPorEtiqueta = buscarArchivosPorEtiqueta( archivosAFiltrar, query );
	std::vector<std::string> archivosEncontradosPorPropietario = buscarArchivosPorPropietario( archivosAFiltrar, query );

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaConRecuperados;
	carpetaConRecuperados.setPath( "archivos/recuperados" );

	for ( unsigned int i = 0 ; i < archivosEncontradosPorNombre.size() ; i++)
	{
		carpetaConRecuperados.agregarArchivo( archivosEncontradosPorNombre[i] );
	}
	for ( unsigned int i = 0 ; i < archivosEncontradosPorExtension.size() ; i++)
	{
		carpetaConRecuperados.agregarArchivo( archivosEncontradosPorExtension[i] );
	}
	for ( unsigned int i = 0 ; i < archivosEncontradosPorEtiqueta.size() ; i++)
	{
		carpetaConRecuperados.agregarArchivo( archivosEncontradosPorEtiqueta[i] );
	}
	for ( unsigned int i = 0 ; i < archivosEncontradosPorPropietario.size() ; i++)
	{
		carpetaConRecuperados.agregarArchivo( archivosEncontradosPorPropietario[i] );
	}

	respuesta.setContenido( carpetaConRecuperados.getContenido() );
	respuesta.setEstado("ok");
	respuesta.setMensaje("Busqueda realizada correctamente!");
	Utiles::Log::instancia()->info("Busqueda realizada.", this->nombreClase() );
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

std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> OperacionBusqueda::getArchivosAFiltrar(std::vector<std::string> paths)
{
	std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> resultado;

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoActual;
	for ( unsigned int i = 0 ; i < paths.size() ; i++)
	{
		archivoActual = new ConexionServidor::BaseDeDatos::ArchivoLogico();
		archivoActual->setPath( paths[i] );

		std::string valorRecuperado = archivoActual->recuperar();
		archivoActual->setContenido( valorRecuperado );

		if ( valorRecuperado.compare("vacio") != 0 )
		{
			resultado.push_back(archivoActual);
		}
	}
	return resultado;
}

std::vector<std::string> OperacionBusqueda::buscarArchivosPorNombre(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivos, std::string query)
{
	std::vector<std::string> resultado;
	for ( unsigned int i = 0 ; i < archivos.size() ; i++)
	{
		if ( archivos[i]->getNombre().compare(query) == 0 )
		{
			resultado.push_back( archivos[i]->getPath() );
		}
	}
	return resultado;
}
std::vector<std::string> OperacionBusqueda::buscarArchivosPorEtiqueta(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivos, std::string query)
{
	std::vector<std::string> resultado;
	for ( unsigned int i = 0 ; i < archivos.size() ; i++)
	{
		std::vector<std::string> etiquetas = archivos[i]->getEtiquetas();
		for ( unsigned int i = 0 ; i < etiquetas.size() ; i++)
		{
			if ( etiquetas[i].compare(query) == 0 )
			{
				resultado.push_back( archivos[i]->getPath() );
			}
		}
	}
	return resultado;
}
std::vector<std::string> OperacionBusqueda::buscarArchivosPorExtension(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivos, std::string query)
{
	std::vector<std::string> resultado;
	for ( unsigned int i = 0 ; i < archivos.size() ; i++)
	{
		if ( archivos[i]->getExtension().compare(query) == 0 )
		{
			resultado.push_back( archivos[i]->getPath() );
		}
	}
	return resultado;
}
std::vector<std::string> OperacionBusqueda::buscarArchivosPorPropietario(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivos, std::string query)
{
	std::vector<std::string> resultado;
	for ( unsigned int i = 0 ; i < archivos.size() ; i++)
	{
		if ( archivos[i]->getPropietario().compare(query) == 0 )
		{
			resultado.push_back( archivos[i]->getPath() );
		}
	}
	return resultado;
}

void OperacionBusqueda::imprimir()
{
	std::cout << "busqueda\n";
}

std::string OperacionBusqueda::nombreClase()
{
	return "OperacionBusqueda";
}
