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
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico = new ConexionServidor::BaseDeDatos::ArchivoLogico( contenido->getStringDeBytes() );
	ConexionServidor::Respuesta respuesta;

	if ( this->acciones.darDeBajaArchivoLogico( archivoLogico ) == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al dar de baja el archivo. 1");
		return respuesta;
	}

	if ( this->acciones.sacarArchivoLogicoDeSuCarpetaLogica( archivoLogico ) == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al dar de baja el archivo. 2");
		return respuesta;
	}

	if ( this->acciones.agregarArchivoLogicoAPapelera( archivoLogico ) == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al dar de baja el archivo. 3");
		return respuesta;
	}

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

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico = this->acciones.parsearArchivoDeQuery( query );

	bool resultadoAltaLogica = this->acciones.darDeAltaArchivoLogico( archivoLogico );

	ConexionServidor::BaseDeDatos::Archivo* archivo = new ConexionServidor::BaseDeDatos::Archivo( archivoLogico->getContenido() );
	archivo->setBytes( contenido );
	bool resultadoAltaFisica= this->acciones.darDeAltaArchivoFisico( archivo );

	if (resultadoAltaLogica == false || resultadoAltaFisica == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al dar de alta el archivo.");
		return respuesta;
	}

	/*bool resultadoAgregarArchivoASuContenido = */this->acciones.agregarArchivoLogicoASuCarpetaLogica( archivoLogico );
	/*bool resultadoAgregarArchivoAContenidoPorUsuario = */this->acciones.agregarArchivoALaListaDeArchivosDeUsuario( archivoLogico );
	/*bool resultadoAgregarVersionDeArchivo = */this->acciones.crearVersionInicialDeArchivo( archivoLogico );

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo dado de alta correctamente!");

	delete archivoLogico;
	delete archivo;

	return respuesta;
}
ConexionServidor::Respuesta OperacionesArchivos::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogicoNuevo = this->acciones.parsearArchivoDeQuery( query );
	ConexionServidor::BaseDeDatos::Archivo* archivoFisicoNuevo = new ConexionServidor::BaseDeDatos::Archivo( archivoLogicoNuevo->getContenido() );
	archivoFisicoNuevo->setBytes( contenido );
	ConexionServidor::Respuesta respuesta;

	if ( this->acciones.versionDeUltimoModificadorEstaActualizada( archivoLogicoNuevo ) == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Version de archivo desactualizada.");
		return respuesta;
	}

	/* bool resultadoModificarArchivoLogico = */ this->acciones.modificarArchivoLogico( archivoLogicoNuevo );

	//bool resultadoModificarArchivoFisico = true;
	if ( contenido->getTamanio() > 0 )
	{
		/* resultadoModificarArchivoFisico = */this->acciones.modificarArchivoFisico( archivoFisicoNuevo );
	}


	this->acciones.actualizarVersionDeUltimoModificador( archivoLogicoNuevo );

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo modificado correctamente!");

	delete archivoLogicoNuevo;
	delete archivoFisicoNuevo;

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

