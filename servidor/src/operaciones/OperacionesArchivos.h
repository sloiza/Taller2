/*
 * OperacionesArchivos.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESARCHIVOS_H_
#define OPERACIONESARCHIVOS_H_

// conexion
#include "../conexion/Respuesta.h"
// base de datos
#include "../archivos/Archivo.h"
// entidades
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesArchivos : public IOperable {

public:
	OperacionesArchivos();
	virtual ~OperacionesArchivos();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	static ConexionServidor::BaseDeDatos::Archivo* archivoTemporal;
	static bool estoyEsperandoLosBytes;
	static void cambiarFlag();
	static void settearContenidoSegunFlag(Utiles::Bytes*);
	static void resettearArchivoTemporalSegunFlag();
	static ConexionServidor::Respuesta respuestaSegunFlag();
	static bool error;
	static bool sobreescribir;
	static void agregarArchivoALaListaDeArchivosPorCarpeta(std::string);
	static void agregarArchivoALaListaDeArchivosDeUsuario(std::string);

};
};
};

#endif /* OPERACIONESARCHIVOS_H_ */
