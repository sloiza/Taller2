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
// Operaciones
#include "IOperable.h"

// base de datos
#include "../archivos/Archivo.h"

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

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();

	static ConexionServidor::BaseDeDatos::Archivo* archivoTemporal;
	static bool estoyEsperandoLosBytes;
	static void cambiarFlag();
	static void settearContenidoSegunFlag(std::string);
	static void resettearArchivoTemporalSegunFlag();

};
};
};

#endif /* OPERACIONESARCHIVOS_H_ */
