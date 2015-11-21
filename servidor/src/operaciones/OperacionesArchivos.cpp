/*
 * OperacionesArchivos.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesArchivos.h"

using namespace ConexionServidor::Operaciones;

bool OperacionesArchivos::sobreescribir = false;
ConexionServidor::BaseDeDatos::Archivo* OperacionesArchivos::archivoTemporal = new ConexionServidor::BaseDeDatos::Archivo();

OperacionesArchivos::OperacionesArchivos() {}

OperacionesArchivos::~OperacionesArchivos() {}

ConexionServidor::Respuesta OperacionesArchivos::delet(Utiles::Bytes* contenido, std::string query)
{
	// 1) settear baja_logica = si
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoLogico( contenido->getStringDeBytes() );
	std::string valorRecuperado = archivoLogico.recuperar();
	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Archivo inexistente.");
		return respuesta;
	}
	archivoLogico.setContenido( valorRecuperado );

	archivoLogico.setBajaLogica("si");
	archivoLogico.guardar();

	// 2) sacarlo de contenidoPorCarpeta
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico.getDireccion() );
	valorRecuperado = contenidoEnCarpeta.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Carpeta inexistente.");
		return respuesta;
	}
	contenidoEnCarpeta.setContenido( valorRecuperado );

	//contenidoEnCarpeta.eliminarArchivo( archivoLogico.getNombreYExtension() );
	contenidoEnCarpeta.eliminarArchivo( archivoLogico.getPath() );

	contenidoEnCarpeta.guardar();
	// 3) agregarlo a la papelera
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( archivoLogico.getPropietario() + "/" + InfoOperaciones::papelera );

//	std::cout << "archivos path papelera: " + archivoLogico.getPropietario() + "/" + InfoOperaciones::papelera << "\n";

	valorRecuperado = papelera.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		papelera.setContenido( valorRecuperado );
	}

	papelera.agregarArchivo( archivoLogico.getPath() );

	papelera.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo dado de baja correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::get(Utiles::Bytes* contenido, std::string query)
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
ConexionServidor::Respuesta OperacionesArchivos::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	std::string datosLogicos = query;

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico = new ConexionServidor::BaseDeDatos::ArchivoLogico( query );
	bool resultadoAltaLogica = this->acciones.darDeAltaArchivoLogico( archivoLogico );

	ConexionServidor::BaseDeDatos::Archivo* archivo = new ConexionServidor::BaseDeDatos::Archivo( query );
	archivo->setBytes( contenido );
	bool resultadoAltaFisica= this->acciones.darDeAltaArchivoFisico( archivo );

	if (resultadoAltaLogica == false || resultadoAltaFisica == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al dar de alta el archivo.");
		return respuesta;
	}

	agregarArchivoALaListaDeArchivosPorCarpeta( datosLogicos );
	agregarArchivoALaListaDeArchivosDeUsuario( datosLogicos );

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo dado de alta correctamente!");

	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::ArchivoLogico archivo(contenido->getStringDeBytes());
	ConexionServidor::Respuesta respuesta;

	std::string valorRecuperado = archivo.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Usuario inexistente.");
		return respuesta;
	}

	archivo.guardar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo modificado correctamente!");
	return respuesta;
}

void OperacionesArchivos::imprimir()
{
	std::cout << "archivos\n";
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

	//contenidoEnCarpeta.agregarArchivo( archivoLogico.getNombreYExtension() );
	contenidoEnCarpeta.agregarArchivo( archivoLogico.getPath() );

	contenidoEnCarpeta.guardar();
}

void OperacionesArchivos::agregarArchivoALaListaDeArchivosDeUsuario(std::string contenido)
{
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoLogico(contenido);

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico.getPropietario() + "/" + InfoOperaciones::carpetaArchivosPorUsuario );

	std::cout << "propietario: " << archivoLogico.getPropietario() << "\n";

	std::string valorRecuperado = contenidoEnCarpeta.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenidoEnCarpeta.setContenido(valorRecuperado);
	}

	//contenidoEnCarpeta.agregarArchivo( archivoLogico.getNombreYExtension() );
	contenidoEnCarpeta.agregarArchivo( archivoLogico.getPath() );

	contenidoEnCarpeta.guardar();

	std::cout << "contenido carpetaArchivos: " << contenidoEnCarpeta.getContenido() << "\n";
}

