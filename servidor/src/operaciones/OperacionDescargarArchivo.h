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

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	void imprimir();
};
};
};

#endif /* OPERACIONDESCARGARARCHIVO_H_ */
