/*
 * OperacionDescargarArchivo.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONDESCARGARARCHIVO_H_
#define OPERACIONDESCARGARARCHIVO_H_

// archivos
#include "../archivos/Archivo.h"
// conexion
#include "../conexion/Respuesta.h"
// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionDescargarArchivo: public IOperable
{
public:
	OperacionDescargarArchivo();
	virtual ~OperacionDescargarArchivo();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();
};
};
};

#endif /* OPERACIONDESCARGARARCHIVO_H_ */
