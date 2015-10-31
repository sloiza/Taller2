/*
 * OperacionDescargarArchivo.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONDESCARGARARCHIVO_H_
#define OPERACIONDESCARGARARCHIVO_H_

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

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();
};
};
};

#endif /* OPERACIONDESCARGARARCHIVO_H_ */
