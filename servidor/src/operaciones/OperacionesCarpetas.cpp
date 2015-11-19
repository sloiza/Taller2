/*
 * OperacionesCarpetas.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionesCarpetas.h"

using namespace ConexionServidor::Operaciones;

OperacionesCarpetas::OperacionesCarpetas() {}

OperacionesCarpetas::~OperacionesCarpetas() {}

ConexionServidor::Respuesta OperacionesCarpetas::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Carpeta carpeta( contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;

	if ( carpeta.existeFisicamente() == false )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		std::cout << "entro a carpeta inexistente\n";
		respuesta.setEstado("carpeta-inexistente");
		respuesta.setMensaje("No existe carpeta con ese nombre.");
		return respuesta;
	}

	if ( carpeta.estaVacia() == false )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		respuesta.setEstado("carpeta-con-contenido");
		respuesta.setMensaje("No se puede eliminar carpeta con contenido.");
		return respuesta;
	}

	// 2) sacarlo de contenidoPorCarpeta
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( carpeta.getDireccion() );
	std::string valorRecuperado = contenidoEnCarpeta.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Carpeta inexistente.");
		return respuesta;
	}
	contenidoEnCarpeta.setContenido( valorRecuperado );

	//contenidoEnCarpeta.eliminarArchivo( archivoLogico.getNombreYExtension() );
	contenidoEnCarpeta.eliminarCarpeta( carpeta.getPath() );

	contenidoEnCarpeta.guardar();

	// 3) agregarlo a la papelera
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( carpeta.getPropietario() + "/" + InfoOperaciones::papelera );

	valorRecuperado = papelera.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		papelera.setContenido( valorRecuperado );
	}

	papelera.agregarCarpeta( carpeta.getPath() );

	papelera.guardar();

	// ---- //
	carpeta.eliminar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta eliminada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesCarpetas::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::CarpetaLogica carpetaLogica( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoDeCarpeta( contenido->getStringDeBytes() );

	std::string valorRecuperadoArchivos = contenidoDeCarpeta.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperadoArchivos.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("No existe carpeta.");
		return respuesta;
	}

	std::string valorRecuperadoDetalles = carpetaLogica.recuperar();

	if ( valorRecuperadoDetalles.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("No existe carpeta.");
		return respuesta;
	}

	if ( query.compare("detalles") == 0 )
	{
		respuesta.setContenido(valorRecuperadoDetalles);
	}
	else
	{
		respuesta.setContenido(valorRecuperadoArchivos);
	}

	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta accedida correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesCarpetas::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Carpeta carpeta( contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;
	if ( carpeta.existeFisicamente() )
	{// si ya existe, no se crea en disco ni se guarda logicamente.
		respuesta.setEstado("carpeta-existente");
		respuesta.setMensaje("Ya existe carpeta con ese nombre.");
		return respuesta;
	}

	carpeta.guardar();

	agregarCarpetaALaListaDeArchivosPorCarpeta( contenido->getStringDeBytes() );

	respuesta.setEstado("ok");
	respuesta.setMensaje("Carpeta creada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesCarpetas::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}

void OperacionesCarpetas::imprimir()
{
	std::cout << "carpetas\n";
}

void OperacionesCarpetas::agregarCarpetaALaListaDeArchivosPorCarpeta(std::string contenido)
{
	ConexionServidor::BaseDeDatos::CarpetaLogica carpetaLogica(contenido);

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( carpetaLogica.getDireccion() );

	std::string valorRecuperado = contenidoEnCarpeta.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenidoEnCarpeta.setContenido(valorRecuperado);
	}

	//contenidoEnCarpeta.agregarArchivo( archivoLogico.getNombreYExtension() );
	contenidoEnCarpeta.agregarCarpeta( carpetaLogica.getPath() );

	contenidoEnCarpeta.guardar();
}
