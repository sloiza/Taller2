/*
 * OperacionDescargarArchivo.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "OperacionDescargarArchivo.h"

using namespace ConexionServidor::Operaciones;

OperacionDescargarArchivo::OperacionDescargarArchivo() {}

OperacionDescargarArchivo::~OperacionDescargarArchivo() {}

ConexionServidor::Respuesta OperacionDescargarArchivo::delet(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionDescargarArchivo->delete" << "\n";
}
ConexionServidor::Respuesta OperacionDescargarArchivo::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Archivo archivoFisico(contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;
	if ( archivoFisico.existeFisicamente() == false)
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Archivo a descargar inexistente.");
		return respuesta;
	}

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo descargado correctamente!");
	respuesta.setEsDescarga(true);
	respuesta.setPathDelArchivoADescargar( archivoFisico.getPath() );
	return respuesta;
}
ConexionServidor::Respuesta OperacionDescargarArchivo::post(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionDescargarArchivo->post" << "\n";
}
ConexionServidor::Respuesta OperacionDescargarArchivo::put(Utiles::Bytes* contenido, std::string query)
{
	std::cout << "OperacionDescargarArchivo->put" << "\n";
}

void OperacionDescargarArchivo::imprimir()
{
	std::cout << "descargar\n";
}
